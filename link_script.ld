OUTPUT_FORMAT("elf32-littlearm")
OUTPUT_ARCH(arm)

MEMORY {
    FLASH   (rw)  : ORIGIN = 0x08000000, LENGTH = 1024K
    SRAM1   (rwx) : ORIGIN = 0x20000000, LENGTH = 112K
    SRAM2   (rwx) : ORIGIN = 0x2001C000, LENGTH = 16K
}

SECTIONS {
    /* Text section. */
    .text : {
        KEEP(*(.isr_vector))
        *(.text)
        *(.text*)
    } > FLASH

    .rodata : {
        *(.rodata)
        *(.rodata*)
    } > FLASH

    /* Data section. */
    _data_flash    = . ;
    .data : AT (_data_flash) {
        _data_begin = . ;
        *(.data)
        *(.data*)
        _data_end  = . ;
        _data_size = _data_end - _data_begin;
    } > SRAM1

    /* BSS; the symbols required by GCC are assigned
     * the locations calculated here. */
    .bss : {
        _bss_begin = . ;
        *(.bss)
        *(.bss*)
        *(COMMON)
        _bss_end   = . ;
        _bss_size  = _bss_end - _bss_begin;
        PROVIDE(__bss_start__ = _bss_begin);
        PROVIDE(__bss_end__   = _bss_end);
    } > SRAM1

    /* Heap, fully ascending, between bss and stack. */
    .heap : {
        _heap_begin = . ;
        *(.heap)
        *(.heap*)
        _heap_end = . ;
        _heap_size = _heap_end - _heap_begin;
        ASSERT(_heap_begin >= _bss_end, "Error: BSS/Heap collision.");
    } > SRAM1

    /* Stack, fully descending. Default size: 1024. */
    .stack : {
        _stack_size  = DEFINED(_stack_size) ? _stack_size : 0x400;
        _stack_end   = ORIGIN(SRAM1) + LENGTH(SRAM1);
        _stack_begin = _stack_end - _stack_size;
        ASSERT(_stack_begin >= _heap_end, "Error: Heap/Stack collision.");
    } > SRAM1

    /DISCARD/ : {
        *(.ARM.attributes)
        *(.comment)
    }
}

ENTRY(_reset_handler)
