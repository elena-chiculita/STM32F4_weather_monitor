    .text


    @ Delay by <r0> miliseconds.
    @ r0 - number of miliseconds
    @ return - none
    @ preserves all registers except r0, r1, r2
    .global delay
    .type   delay, %function
delay:
    cmp     r0, #0              @ compare number of miliseconds with 0
    beq     delay_end           @ if equal jump to end
    mov     r2, #0xc0           @ r2 = 0xc0 (value was manually adjusted to ensure the accuracy is good enough)
delay_ms:
    mov     r1, #0xf0           @ r1 = 0xf0 (value was manually adjusted to ensure the accuracy is good enough)
    lsl     r1, r1, #4          @ r1 = r1 << 4
    orr     r1, r1, r2          @ r1 |= 0xc0
delay_counter:
    sub     r1, #1              @ decrement counter
    cmp     r1, #0              @ compare counter with 0
    bne     delay_counter       @ if not equal continue
    sub     r0, #1              @ decrement numnber of miliseconds
    cmp     r0, #0              @ compare number of miliseconds with 0
    bne     delay_ms            @ if not equal continue
delay_end:
    bx      lr                  @ return (pc = lr)
    .size   delay, . - delay
