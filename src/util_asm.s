    @ Set <r2> bytes to <r1> value starting from address <r0>.
    @ r0 - buffer address
    @ r1 - value
    @ r2 - number of bytes to set
    @ return r0 - buffer address
    @ preserves all registers except r0, r1, r3 (should be equal to r2 in the end)
    .global memset
    .type   memset, %function
memset:
    push    {r4}                @ preserve r4
    push    {r5}                @ preserve r5
    cmp     r2, #0              @ compare number of bytes with 0
    beq     memset_end          @ if number of bytes is 0 go straight to end
    mov     r3, #0              @ set offset to 0
    mov     r4, #255            @ set mask to 0xff for casting to uint8_t
    and     r1, r1, r4          @ convert value from r1 to uint8_t
    mov     r5, r1              @ r5 = value << 0
    lsl     r5, r5, #8          @ r5 = value << 8
    orr     r1, r1, r5          @ r1 = (value << 8) | (value)
    lsl     r5, r5, #8          @ r5 = value << 16
    orr     r1, r1, r5          @ r1 = (value << 16) | (value << 8) | (value)
    lsl     r5, r5, #8          @ r5 = value << 24
    orr     r1, r1, r5          @ r1 = (value << 24) | (value << 16) | (value << 8) | (value)
    mov     r5, r0              @ temporary copy of buffer address (because of AND syntax : Rd = Rd AND Rn)
    mov     r4, #3              @ r4 = b11
    and     r5, r5, r4          @ r5 = r0 & b11 ; (number of bytes to the next aligned address)
    cmp     r5, #0              @ compare number of bytes to the next aligned addres with 0
    beq     memset_cmp          @ if 0 jump to check if to copy bytes or words
memset_not_aligned:
    strb    r1, [r0, r3]        @ [r0 + r3] = r1 ; (copy LSB from r1 to [r0 + r3] address)
    add     r3, r3, #1          @ increment offset
    cmp     r3, r5              @ compare offset with number of bytes to the next aligned address
    bne     memset_not_aligned  @ repeat until aligned address is reached
memset_cmp:
    sub     r4, r2, r5          @ r4 = total number of bytes - non-aligned bytes
    cmp     r4, #0              @ compare number of bytes to set with 0
    beq     memset_end          @ if no more bytes left to set go straight to end
    cmp     r4, #3              @ compare number of bytes to set with 3
    ble     memset_set_b        @ ble = branch signed less than or equal (1, 2 or 3 bytes to set)
memset_set_w:
    str     r1, [r0, r3]        @ [r0 + r3] = r1 ; (copy 32-bits from r1 to [r0 + r3] address)
    add     r3, r3, #4          @ push offset forward by 32-bits
    sub     r4, r2, r3          @ r4 = r2 - r3 ; (number of bytes left to set)
    cmp     r4, #3              @ compare the result with 3
    bhi     memset_set_w        @ bhi = branch unsigned higher (at least 4 bytes left to set)
    cmp     r4, #0              @ check if there are more bytes to set
    beq     memset_end          @ if not go straight to the end
memset_set_b:
    strb    r1, [r0, r3]        @ [r0 + r3] = r1 ; (copy LSB from r1 to [r0 + r3] address)
    add     r3, r3, #1          @ push offset forward by 8-bits
    cmp     r2, r3              @ check if there are more bytes to set
    bne     memset_set_b        @ repeat if there are bytes left to set
memset_end:
    pop     {r5}                @ restore preserved r5
    pop     {r4}                @ restore preserved r4
    bx      lr                  @ return (pc = lr)
    .size memset, . - memset


    @ Copy <r2> bytes from address <r1> to address <r0>.
    @ r0 - destination buffer address
    @ r1 - source buffer address
    @ r2 - number of bytes to copy
    @ return r0 - destination buffer address
    @ preserves all registers except r0, r3 (should be equal to r2 in the end)
    .global memcpy
    .type   memcpy, %function
memcpy:
    push    {r4}                @ preserve r4
    push    {r5}                @ preserve r5
    push    {r6}                @ preserve r6
    cmp     r2, #0              @ compare number of bytes with 0
    beq     memcpy_end          @ if number of bytes is 0 go straight to end
    mov     r3, #0              @ set offset to 0
    cmp     r2, #3              @ compare number of bytes with 3
    bls     memcpy_copy_b       @ if less than or equal to 3 jump to copy bytes
    mov     r4, r0              @ temporary copy of destination address (because of AND syntax : Rd = Rd AND Rn)
    mov     r5, r1              @ temporary copy of source address (because of AND syntax : Rd = Rd AND Rn)
    mov     r6, #3              @ r6 = b11
    and     r4, r4, r6          @ r4 = r0 & b11 ; (number of bytes to the next destination aligned address)
    and     r5, r5, r6          @ r5 = r1 & b11 ; (number of bytes to the next source aligned address)
    add     r6, r4, r5          @ add the alignments of both destination and source
    cmp     r6, #0              @ compare result with 0
    beq     memcpy_copy_w       @ if result is 0 then both destination and source are aligned
                                @ jump to copy words
                                @ r2 >= 4 ; (at this point number of bytes to copy is greater than or equal to 4)
    sub     r6, r4, r5          @ alignment difference between destination and source
    bpl     memcpy_bpl          @ r4 >= r5 ; (jump for copy until the next aligned address)
    mov     r6, r4              @ r4 < r5 ; (switch their contents for later subtraction)
    mov     r4, r5
    mov     r5, r6
    sub     r6, r4, r5          @ get difference between alignment of destination and source
memcpy_bpl:
    cmp     r6, #1              @ compare the result with 1
    beq     memcpy_copy_b       @ jump to copy bytes until the end
    cmp     r6, #3              @ compare the result with 3
    beq     memcpy_copy_b       @ jump to copy bytes until the end
    cmp     r5, #0              @ at this point r6 == 2, destination and source are at 2 byte offset
                                @ (r5 == 0) ? destination or source are aligned = copy 2 bytes
                                @ (r5 == 1) ? copy 1 byte to align destination and source at 2 bytes
    beq     memcpy_copy_hw      @ r5 == 0 ; jump to copy halfwords
    ldrb    r4, [r1, r3]        @ r4 = [r1 + r3] ; (copy 8-bits from [r1 + r3] address to r4)
    strb    r4, [r0, r3]        @ [r0 + r3] = r4 ; (copy 8-bits from r4 to [r0 + r3] address)
    add     r3, r3, #1          @ increment offset
    b       memcpy_copy_hw      @ destination and source are at 2 byte offset, jump to copy halfwords
memcpy_copy_b:
    ldrb    r4, [r1, r3]        @ r4 = [r1 + r3] ; (copy 8-bits from [r1 + r3] address to r4)
    strb    r4, [r0, r3]        @ [r0 + r3] = r4 ; (copy 8-bits from r4 to [r0 + r3] address)
    add     r3, r3, #1          @ push offset forward by 8-bits
    cmp     r3, r2              @ check if there are more bytes left to copy
    bne     memcpy_copy_b       @ repeat
    beq     memcpy_end          @ until no more bytes to copy
memcpy_copy_hw:
    ldrh    r4, [r1, r3]        @ r4 = [r1 + r3] ; (copy 16-bits from [r1 + r3] address to r4)
    strh    r4, [r0, r3]        @ [r0 + r3] = r4 ; (copy 16-bits from r4 to [r0 + r3] address)
    add     r3, r3, #2          @ push offset forward by 16-bits
    sub     r6, r2, r3          @ get the number of bytes left to copy
    cmp     r6, #1              @ compare with 2
    bhi     memcpy_copy_hw      @ if there are at least 2 bytes left to copy repeat copying 16-bits
    cmp     r6, #0              @ check if there are bytes left to copy
    beq     memcpy_end          @ if no more bytes to copy go straight to end
    b       memcpy_copy_b       @ if not jump to copy 8-bits
memcpy_copy_w:
    ldr     r4, [r1, r3]        @ r4 = [r1 + r3] ; (copy 32-bits from [r1 + r3] address to r4)
    str     r4, [r0, r3]        @ [r0 + r3] = r4 ; (copy 32-bits from r4 to [r0 + r3] address)
    add     r3, r3, #4          @ push offset forward by 32-bits
    sub     r6, r2, r3          @ get the number of bytes left to copy
    cmp     r6, #3              @ compare with 3
    bhi     memcpy_copy_w       @ if there are at least 4 bytes left to copy repeat copying 32-bits
    cmp     r6, #0              @ check if there are bytes left to copy
    beq     memcpy_end          @ if no more bytes to copy go straight to end
    b       memcpy_copy_b       @ if not jump to copy 8-bits
memcpy_end:
    pop     {r6}                @ restore preserved r6
    pop     {r5}                @ restore preserved r5
    pop     {r4}                @ restore preserved r4
    bx      lr                  @ return (pc = lr)
    .size memcpy, . - memcpy
