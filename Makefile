include Makefile.in

INCLUDES        = -Iinc
DEFINES         =
LDFLAGS         = -static -nostartfiles -nostdlib -nodefaultlibs \
			-Tlink_script.ld -Wl,-Map=$(MAP_NAME)
LDFLAGS_RELEASE = -flto -Wl,-gc-sections -Wl,-print-gc-sections
MCU_FLAGS       = -mcpu=cortex-m4 -mlittle-endian -mthumb -mfloat-abi=soft
ASFLAGS         = --warn -EL $(MCU_FLAGS) -mfpu=softvfp
ASFLAGS_DEBUG   = -g
CFLAGS          = -c -std=c11 -Wall -Wextra -fno-common -ffreestanding \
			-ffunction-sections -fdata-sections $(MCU_FLAGS)
CFLAGS_RELEASE  = -Os -flto
CFLAGS_DEBUG    = -Og -ggdb3

SOURCES_CC_COMMON = core_irq_handlers.c \
                    gpio.c \
                    led.c \
                    hal_lcd.c \
                    lcd.c \
                    util.c \
                    lib.c
SOURCES_CC_BUILD = main.c
SOURCES_CC_TEST = main_test.c \
                  util_test.c
SOURCES_AS = startup.s \
             util_asm.s

ifeq ($(MAKECMDGOALS), debug)
	SOURCES_CC = $(SOURCES_CC_COMMON) $(SOURCES_CC_BUILD)
	CFLAGS  += $(CFLAGS_DEBUG)
	ASFLAGS += $(ASFLAGS_DEBUG)
	VARIANT = debug
else ifeq ($(MAKECMDGOALS), test)
	SOURCES_CC = $(SOURCES_CC_COMMON) $(SOURCES_CC_TEST)
	CFLAGS  += $(CFLAGS_DEBUG)
	ASFLAGS += $(ASFLAGS_DEBUG)
	VARIANT = test
	DEFINES += TARGET_TEST
else ifeq ($(MAKECMDGOALS), release)
	SOURCES_CC = $(SOURCES_CC_COMMON) $(SOURCES_CC_BUILD)
	CFLAGS  += $(CFLAGS_RELEASE)
	LDFLAGS += $(LDFLAGS_RELEASE)
	VARIANT = release
else
	SOURCES_CC = $(SOURCES_CC_COMMON) $(SOURCES_CC_BUILD)
	CFLAGS  += $(CFLAGS_DEBUG)
	ASFLAGS += $(ASFLAGS_DEBUG)
	VARIANT = debug
endif

SRCDIR = src
BUILDROOT = build
BUILDDIR = $(BUILDROOT)/$(VARIANT)

IMAGE = $(BUILDDIR)/image
ELF_NAME = $(IMAGE).elf
BINARY_NAME = $(IMAGE).bin
LISTING_NAME = $(IMAGE).lst
MAP_NAME = $(IMAGE).map

# Each define will have -D prepended
DEFINES_PRE = $(DEFINES:%=-D%)

# Each C and ASM source file will have SRCDIR prepended
SOURCES_CC_PRE = $(SOURCES_CC:%=$(SRCDIR)/%)
SOURCES_AS_PRE = $(SOURCES_AS:%=$(SRCDIR)/%)

# Replace .c/.s with .o in these to obtain the objects
OBJECTS_CC = $(SOURCES_CC_PRE:.c=.o)
OBJECTS_AS = $(SOURCES_AS_PRE:.s=.o)

# Prepend BUILDDIR to each previous object file
OBJECTS_CC_DEST = $(OBJECTS_CC:%=$(BUILDDIR)/%)
OBJECTS_AS_DEST = $(OBJECTS_AS:%=$(BUILDDIR)/%)


all: debug

.PHONY: release
release: clean build

.PHONY: debug
debug: build

.PHONY: test
test: build

.PHONY: build
build: $(ELF_NAME) $(LISTING_NAME) $(BINARY_NAME)

$(ELF_NAME): $(BUILDDIR)/$(SRCDIR) $(OBJECTS_AS_DEST) $(OBJECTS_CC_DEST)
	@$(ECHO) "\nCreating $@"
	$(LD) $(LDFLAGS) $(OBJECTS_AS_DEST) $(OBJECTS_CC_DEST) -o $@
	-$(FILE) $(ELF_NAME)
	-$(OBJDUMP) -h -j .text -j .rodata -j .data -j .bss $(ELF_NAME)
	@$(ECHO) "\n"

$(LISTING_NAME): $(ELF_NAME)
	@$(ECHO) "Creating $@\n"
	-$(OBJDUMP) -d -S -l $(ELF_NAME) > $(LISTING_NAME)

$(BINARY_NAME): $(ELF_NAME)
	@$(ECHO) "Creating $@\n"
	-$(OBJCOPY) -O binary $(ELF_NAME) $(BINARY_NAME)

$(BUILDDIR)/%.o : %.c
	@$(ECHO) "Building $@ from $<"
	$(CC) -MT $@ -MMD -MP -MF $(@:.o=.d) \
		$(CFLAGS) $(INCLUDES) $(DEFINES_PRE) $< -o $@

$(BUILDDIR)/%.o : %.s
	@$(ECHO) "Building $@ from $<"
	$(AS) $(ASFLAGS) $< -o $@

$(BUILDDIR)/$(SRCDIR):
	@$(ECHO) "Creating $(BUILDDIR)/$(SRCDIR)"
	$(MKDIR) -p $(BUILDDIR)/$(SRCDIR)

.PHONY: clean
clean:
	@$(ECHO) "Deleting $(BUILDROOT)"
	-@$(RM) $(BUILDROOT)


# Include dependency files (.d) if they exist.
# Keep this line at the end of the file.
-include $(OBJECTS_CC_DEST:.o=.d)
