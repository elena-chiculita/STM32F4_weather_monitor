    .cpu    cortex-m4
    .syntax unified
    .thumb

    .text

     @ Reset handler/entry point is here. Copy data from ROM
     @ to RAM, zero BSS, branch to main.
    .global _reset_handler
    .type   _reset_handler, %function
_reset_handler:
data_init:
    ldr     r0, =_data_begin            @ copy _data_begin address in r0
    ldr     r1, =_data_end              @ copy _data_end address in r1
    ldr     r2, =_data_flash            @ copy _data_flash address in r2
    cmp     r0, r1                      @ compare _data_begin with _data_end
    beq     data_end                    @ if they are equal jump to zero out the .bss
                                        @ copy data using memcpy with parameters r0, r1 and r2 as follows:
                                        @ r0 - destination adddress
                                        @ r1 - source adddress
                                        @ r2 - number of bytes to copy
    sub     r3, r1, r0                  @ _data_end - _data_begin = number of bytes to copy
    mov     r1, r2                      @ r1 must hold the source address
    mov     r2, r3                      @ r2 must hold the number of bytes to copy
    bl      memcpy                      @ lr = address of next instruction ; pc = memcpy() address
data_end:
    b       bss_init
bss_init:
    ldr     r0, =_bss_begin             @ copy _bss_begin address in r0
    ldr     r1, =_bss_end               @ copy _bss_end address in r1
    cmp     r0, r1                      @ compare _bss_begin with _bss_end
    beq     bss_end                     @ if they are equal jump to main
                                        @ zero out .bss using memset with parameters r0, r1 and r2 as follows:
                                        @ r0 - destination adddress (_bss_begin)
                                        @ r1 - value to set (0)
                                        @ r2 - number of bytes to set
    sub     r3, r1, r0                  @ _bss_end - _bss_begin = number of bytes to set
    mov     r1, #0                      @ r1 must hold the value to set (0)
    mov     r2, r3                      @ r2 must hold the number of bytes to set
    bl      memset                      @ lr = address of next instruction ; pc = memset() address
bss_end:
    bl      main                        @ lr = address of next instruction ; pc = main() address
    b       .                           @ Should never get here but guarding
                                        @ nonetheless, to save debug pain.
    .size _reset_handler, . - _reset_handler


    .global _default_handler
    .type   _default_handler, %function
_default_handler:
        b       .
    .size _default_handler, . - _default_handler


    .section .isr_vector, "a", %progbits
    .type _isr_vectors, %object
    .size _isr_vectors, . - _isr_vectors
_isr_vectors:
    .word _stack_end
    .word _reset_handler
    .word _nmi_handler
    .word _hardfault_handler
    .word _memmgtfault_handler
    .word _busfault_handler
    .word _usagefault_handler
    .word 0 @ Reserved.
    .word 0 @ Reserved.
    .word 0 @ Reserved.
    .word 0 @ Reserved.
    .word _svcall_handler
    .word 0 @ Reserved.
    .word 0 @ Reserved.
    .word _pendsv_handler
    .word _systick_handler
    @ IRQs from here.

    @ Give handlers/ISRs weak bindings here so that they
    @ can be overridden later by any function with the same
    @ name. Default is _default_handler.
    .weak _nmi_handler
    .thumb_set _nmi_handler,                    _default_handler

    .weak _hardfault_handler
    .thumb_set _hardfault_handler,              _default_handler

    .weak _memmgtfault_handler
    .thumb_set _memmgtfault_handler,            _default_handler

    .weak _busfault_handler
    .thumb_set _busfault_handler,               _default_handler

    .weak _usagefault_handler
    .thumb_set _usagefault_handler,             _default_handler

    .weak _svcall_handler
    .thumb_set _svcall_handler,                 _default_handler

    .weak _pendsv_handler
    .thumb_set _pendsv_handler,                 _default_handler

    .weak _systick_handler
    .thumb_set _systick_handler,                _default_handler
