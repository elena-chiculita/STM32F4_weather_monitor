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
    movs    r3, #0
    ldr     r0, =_data_begin
    ldr     r1, =_data_end
    ldr     r2, =_data_flash
    cmp     r0, r1
    beq     data_end
data_copy:
    adds    r4, r0, r3
    ldr     r5, [r2, r3] 
    str     r5, [r0, r3]
    adds    r3, r3, #4
    cmp     r4, r1
    bne     data_copy
data_end:
    b       bss_init
bss_init:                              @ Zero out the .bss
    movs    r2, #0
    ldr     r0, =_bss_begin
    ldr     r1, =_bss_end
    cmp     r0, r1
    beq     bss_end
bss_zero:
    str     r2, [r0, #0]
    adds    r0, r0, #4
    cmp     r0, r1
    bne     bss_zero
bss_end:
    bl      main
    b       .                          @ Should never get here but guarding
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
