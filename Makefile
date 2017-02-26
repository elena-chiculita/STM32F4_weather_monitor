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

ifdef release
CFLAGS  += $(CFLAGS_RELEASE)
LDFLAGS += $(LDFLAGS_RELEASE)
VARIANT  = release
else
CFLAGS  += $(CFLAGS_DEBUG)
ASFLAGS += $(ASFLAGS_DEBUG)
VARIANT  = debug
endif

SRCDIR    = src
BUILDROOT = build
BUILDDIR  = $(BUILDROOT)/$(VARIANT)

TARGET          = $(BUILDDIR)/image
ELF_NAME        = $(TARGET).elf
BINARY_NAME     = $(TARGET).bin
LISTING_NAME    = $(TARGET).lst
MAP_NAME        = $(TARGET).map

SOURCES_CC = core_irq_handlers.c \
             main.c \
             gpio.c \
             led.c \
             hal_lcd.c \
             lcd.c \
             util.c
SOURCES_AS = startup.s \
             util_asm.s

SOURCES_CC_PRE = $(SOURCES_CC:%=$(SRCDIR)/%)
SOURCES_AS_PRE = $(SOURCES_AS:%=$(SRCDIR)/%)
OBJECTS_CC = $(SOURCES_CC_PRE:.c=.o)
OBJECTS_AS = $(SOURCES_AS_PRE:.s=.o)
# This isn't very pretty, but the premise here is to
# output object files to the build directory along
# with the ELF and friends. This is desirable, but
# is made awkward by {b,p}make transformation rules,
# which aren't quite as flexible as gmake pattern
# rules... Long story short, all object code shall
# be outputted to the build directory.
OBJECTS_CC_DEST = $(OBJECTS_CC:%=$(BUILDDIR)/%)
OBJECTS_AS_DEST = $(OBJECTS_AS:%=$(BUILDDIR)/%)

all: debug

.PHONY: release
release: clean build

.PHONY: debug
debug: build

.PHONY: build
build: dir $(OBJECTS_AS) $(OBJECTS_CC)
	$(LD) $(LDFLAGS) $(OBJECTS_AS_DEST) $(OBJECTS_CC_DEST) -o $(ELF_NAME) $(LDLIBS)
	@$(ECHO) "====="
	-$(FILE) $(ELF_NAME)
	@$(ECHO) "====="
	-$(OBJDUMP) -d -S -l $(ELF_NAME) > $(LISTING_NAME)
	-$(OBJCOPY) -O binary $(ELF_NAME) $(BINARY_NAME)
	@$(ECHO) "====="
	-$(OBJDUMP) -h -j .text -j .rodata -j .data -j .bss $(ELF_NAME)
	@$(ECHO) "====="

.c.o:
	$(CC) $(CFLAGS) $(INCLUDES) $(DEFINES) $< -o $(BUILDDIR)/$@

.s.o:
	$(AS) $(ASFLAGS) $< -o $(BUILDDIR)/$@

dir:
	$(MKDIR) -p $(BUILDDIR)/$(SRCDIR)

.PHONY: clean
clean:
	-$(RM) -rf $(BUILDROOT)

.SUFFIXES: .c .s .o
