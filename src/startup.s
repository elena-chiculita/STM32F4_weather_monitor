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
    .word _wwdg_handler
    .word _pvd_handler
    .word _tamp_stamp_handler
    .word _rtc_wkup_handler
    .word _flash_handler
    .word _rcc_handler
    .word _exti0_handler
    .word _exti1_handler
    .word _exti2_handler
    .word _exti3_handler
    .word _exti4_handler
    .word _dma1_stream0_handler
    .word _dma1_stream1_handler
    .word _dma1_stream2_handler
    .word _dma1_stream3_handler
    .word _dma1_stream4_handler
    .word _dma1_stream5_handler
    .word _dma1_stream6_handler
    .word _adc_handler
    .word _can1_tx_handler
    .word _can1_rx0_handler
    .word _can1_rx1_handler
    .word _can1_sce_handler
    .word _exti9_5_handler
    .word _tim1_brk_tim9_handler
    .word _tim1_up_tim10_handler
    .word _tim1_trg_com_tim11_handler
    .word _tim1_cc_handler
    .word _tim2_handler
    .word _tim3_handler
    .word _tim4_handler
    .word _i2c1_ev_handler
    .word _i2c1_er_handler
    .word _i2c2_ev_handler
    .word _i2c2_er_handler
    .word _spi1_handler
    .word _spi2_handler
    .word _usart1_handler
    .word _usart2_handler
    .word _usart3_handler
    .word _exti15_10_handler
    .word _rtc_alarm_handler
    .word _otg_fs_handler
    .word _tim8_brk_tim12_handler
    .word _tim8_up_tim13_handler
    .word _tim8_trg_com_tim14_handler
    .word _tim8_cc_handler
    .word _dma1_stream7_handler
    .word _fsmc_handler
    .word _sdio_handler
    .word _tim5_handler
    .word _spi3_handler
    .word _uart4_handler
    .word _uart5_handler
    .word _tim6_dac_handler
    .word _tim7_handler
    .word _dma2_stream0_handler
    .word _dma2_stream1_handler
    .word _dma2_stream2_handler
    .word _dma2_stream3_handler
    .word _dma2_stream4_handler
    .word _eth_handler
    .word _eth_wkup_handler
    .word _can2_tx_handler
    .word _can2_rx0_handler
    .word _can2_rx1_handler
    .word _can2_sce_handler
    .word _otg_fs_handler
    .word _dma2_stream5_handler
    .word _dma2_stream6_handler
    .word _dma2_stream7_handler
    .word _usart6_handler
    .word _i2c3_ev_handler
    .word _i2c3_er_handler
    .word _otg_hs_ep1_out_handler
    .word _otg_hs_ep1_in_handler
    .word _otg_hs_wkup_handler
    .word _otg_hs_handler
    .word _dcmi_handler
    .word _cryp_handler
    .word _hash_rng_handler
    .word _fpu_handdler

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

    .weak _wwdg_handler
    .thumb_set _wwdg_handler,                   _default_handler

    .weak _pvd_handler
    .thumb_set _pvd_handler,                    _default_handler

    .weak _tamp_stamp_handler
    .thumb_set _tamp_stamp_handler,             _default_handler

    .weak _rtc_wkup_handler
    .thumb_set _rtc_wkup_handler,               _default_handler

    .weak _flash_handler
    .thumb_set _flash_handler,                  _default_handler

    .weak _rcc_handler
    .thumb_set _rcc_handler,                    _default_handler

    .weak _exti0_handler
    .thumb_set _exti0_handler,                  _default_handler

    .weak _exti1_handler
    .thumb_set _exti1_handler,                  _default_handler

    .weak _exti2_handler
    .thumb_set _exti2_handler,                  _default_handler

    .weak _exti3_handler
    .thumb_set _exti3_handler,                  _default_handler

    .weak _exti4_handler
    .thumb_set _exti4_handler,                  _default_handler

    .weak _dma1_stream0_handler
    .thumb_set _dma1_stream0_handler,           _default_handler

    .weak _dma1_stream1_handler
    .thumb_set _dma1_stream1_handler,           _default_handler

    .weak _dma1_stream2_handler
    .thumb_set _dma1_stream2_handler,           _default_handler

    .weak _dma1_stream3_handler
    .thumb_set _dma1_stream3_handler,           _default_handler

    .weak _dma1_stream4_handler
    .thumb_set _dma1_stream4_handler,           _default_handler

    .weak _dma1_stream5_handler
    .thumb_set _dma1_stream5_handler,           _default_handler

    .weak _dma1_stream6_handler
    .thumb_set _dma1_stream6_handler,           _default_handler

    .weak _adc_handler
    .thumb_set _adc_handler,                    _default_handler

    .weak _can1_tx_handler
    .thumb_set _can1_tx_handler,                _default_handler

    .weak _can1_rx0_handler
    .thumb_set _can1_rx0_handler,               _default_handler

    .weak _can1_rx1_handler
    .thumb_set _can1_rx1_handler,               _default_handler

    .weak _can1_sce_handler
    .thumb_set _can1_sce_handler,               _default_handler

    .weak _exti9_5_handler
    .thumb_set _exti9_5_handler,                _default_handler

    .weak _tim1_brk_tim9_handler
    .thumb_set _tim1_brk_tim9_handler,          _default_handler

    .weak _tim1_up_tim10_handler
    .thumb_set _tim1_up_tim10_handler,          _default_handler

    .weak _tim1_trg_com_tim11_handler
    .thumb_set _tim1_trg_com_tim11_handler,     _default_handler

    .weak _tim1_cc_handler
    .thumb_set _tim1_cc_handler,                _default_handler

    .weak _tim2_handler
    .thumb_set _tim2_handler,                   _default_handler

    .weak _tim3_handler
    .thumb_set _tim3_handler,                   _default_handler

    .weak _tim4_handler
    .thumb_set _tim4_handler,                   _default_handler

    .weak _i2c1_ev_handler
    .thumb_set _i2c1_ev_handler,                _default_handler

    .weak _i2c1_er_handler
    .thumb_set _i2c1_er_handler,                _default_handler

    .weak _i2c2_ev_handler
    .thumb_set _i2c2_ev_handler,                _default_handler

    .weak _i2c2_er_handler
    .thumb_set _i2c2_er_handler,                _default_handler

    .weak _usart1_handler
    .thumb_set _usart1_handler,                 _default_handler

    .weak _usart2_handler
    .thumb_set _usart2_handler,                 _default_handler

    .weak _usart3_handler
    .thumb_set _usart3_handler,                 _default_handler

    .weak _exti15_10_handler
    .thumb_set _exti15_10_handler,              _default_handler

    .weak _rtc_alarm_handler
    .thumb_set _rtc_alarm_handler,              _default_handler

    .weak _otg_fs_handler
    .thumb_set _otg_fs_handler,                 _default_handler

    .weak _tim8_brk_tim12_handler
    .thumb_set _tim8_brk_tim12_handler,         _default_handler

    .weak _tim8_up_tim13_handler
    .thumb_set _tim8_up_tim13_handler,          _default_handler

    .weak _tim8_trg_com_tim14_handler
    .thumb_set _tim8_trg_com_tim14_handler,     _default_handler

    .weak _tim8_cc_handler
    .thumb_set _tim8_cc_handler,                _default_handler

    .weak _dma1_stream7_handler
    .thumb_set _dma1_stream7_handler,           _default_handler

    .weak _fsmc_handler
    .thumb_set _fsmc_handler,                   _default_handler

    .weak _sdio_handler
    .thumb_set _sdio_handler,                   _default_handler

    .weak _tim5_handler
    .thumb_set _tim5_handler,                   _default_handler

    .weak _uart4_handler
    .thumb_set _uart4_handler,                  _default_handler

    .weak _uart5_handler
    .thumb_set _uart5_handler,                  _default_handler

    .weak _tim6_dac_handler
    .thumb_set _tim6_dac_handler,               _default_handler

    .weak _tim7_handler
    .thumb_set _tim7_handler,                   _default_handler

    .weak _dma2_stream0_handler
    .thumb_set _dma2_stream0_handler,           _default_handler

    .weak _dma2_stream1_handler
    .thumb_set _dma2_stream1_handler,           _default_handler

    .weak _dma2_stream2_handler
    .thumb_set _dma2_stream2_handler,           _default_handler

    .weak _dma2_stream3_handler
    .thumb_set _dma2_stream3_handler,           _default_handler

    .weak _dma2_stream4_handler
    .thumb_set _dma2_stream4_handler,           _default_handler

    .weak _eth_handler
    .thumb_set _eth_handler,                    _default_handler

    .weak _eth_wkup_handler
    .thumb_set _eth_wkup_handler,               _default_handler

    .weak _can2_tx_handler
    .thumb_set _can2_tx_handler,                _default_handler

    .weak _can2_rx0_handler
    .thumb_set _can2_rx0_handler,               _default_handler

    .weak _can2_rx1_handler
    .thumb_set _can2_rx1_handler,               _default_handler

    .weak _can2_sce_handler
    .thumb_set _can2_sce_handler,               _default_handler

    .weak _otg_fs_handler
    .thumb_set _otg_fs_handler,                 _default_handler

    .weak _dma2_stream5_handler
    .thumb_set _dma2_stream5_handler,           _default_handler

    .weak _dma2_stream6_handler
    .thumb_set _dma2_stream6_handler,           _default_handler

    .weak _dma2_stream7_handler
    .thumb_set _dma2_stream7_handler,           _default_handler

    .weak _usart6_handler
    .thumb_set _usart6_handler,                 _default_handler

    .weak _i2c3_ev_handler
    .thumb_set _i2c3_ev_handler,                _default_handler

    .weak _i2c3_er_handler
    .thumb_set _i2c3_er_handler,                _default_handler

    .weak _otg_hs_ep1_out_handler
    .thumb_set _otg_hs_ep1_out_handler,         _default_handler

    .weak _otg_hs_ep1_in_handler
    .thumb_set _otg_hs_ep1_in_handler,          _default_handler

    .weak _otg_hs_wkup_handler
    .thumb_set _otg_hs_wkup_handler,            _default_handler

    .weak _otg_hs_handler
    .thumb_set _otg_hs_handler,                 _default_handler

    .weak _dcmi_handler
    .thumb_set _dcmi_handler,                   _default_handler

    .weak _cryp_handler
    .thumb_set _cryp_handler,                   _default_handler

    .weak _hash_rng_handler
    .thumb_set _hash_rng_handler,               _default_handler

    .weak _fpu_handdler
    .thumb_set _fpu_handdler,                   _default_handler
