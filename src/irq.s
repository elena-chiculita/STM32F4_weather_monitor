    .text


    @ Read CONTROL register
    @ return - CONTROL register content
    @ preserves all registers except r0
    .global core_reg_get_control
    .type   core_reg_get_control, %function
core_reg_get_control:
    MRS     r0, CONTROL         @ r0 = CONTROL
    bx      lr                  @ return (pc = lr)
    .size   core_reg_get_control, . - core_reg_get_control


    @ Write CONTROL register
    @ r0 - value
    @ return - none
    @ preserves all registers except r0
    .global core_reg_set_control
    .type   core_reg_set_control, %function
core_reg_set_control:
    MSR     CONTROL, r0         @ CONTROL = r0
    bx      lr                  @ return (pc = lr)
    .size   core_reg_set_control, . - core_reg_set_control
