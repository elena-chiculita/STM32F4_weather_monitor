    .text


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
    beq     memset_aligned      @ if 0 jump to check if to copy bytes or words
memset_not_aligned:
    strb    r1, [r0, r3]        @ [r0 + r3] = r1 ; (copy LSB from r1 to [r0 + r3] address)
    add     r3, r3, #1          @ increment offset
    cmp     r3, r5              @ compare offset with number of bytes to the next aligned address
    bne     memset_not_aligned  @ repeat until aligned address is reached
memset_aligned:
    sub     r4, r2, r5          @ r4 = total number of bytes - non-aligned bytes
    cmp     r4, #0              @ compare number of bytes to set with 0
    beq     memset_end          @ if no more bytes left to set go straight to end
    cmp     r4, #3              @ compare number of bytes to set with 3
    ble     memset_b            @ ble = branch signed less than or equal (1, 2 or 3 bytes to set)
memset_w:
    str     r1, [r0, r3]        @ [r0 + r3] = r1 ; (copy 32-bits from r1 to [r0 + r3] address)
    add     r3, r3, #4          @ push offset forward by 32-bits
    sub     r4, r2, r3          @ r4 = r2 - r3 ; (number of bytes left to set)
    cmp     r4, #3              @ compare the result with 3
    bhi     memset_w            @ bhi = branch unsigned higher (at least 4 bytes left to set)
    cmp     r4, #0              @ check if there are more bytes to set
    beq     memset_end          @ if not go straight to the end
memset_b:
    strb    r1, [r0, r3]        @ [r0 + r3] = r1 ; (copy LSB from r1 to [r0 + r3] address)
    add     r3, r3, #1          @ push offset forward by 8-bits
    cmp     r2, r3              @ check if there are more bytes to set
    bne     memset_b            @ repeat if there are bytes left to set
memset_end:
    pop     {r5}                @ restore preserved r5
    pop     {r4}                @ restore preserved r4
    bx      lr                  @ return (pc = lr)
    .size   memset, . - memset


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
    cmp     r0, r1              @ compare destination and source addresses
    beq     memcpy_end          @ if these are equal go straight to end
    mov     r3, #0              @ set offset to 0
    cmp     r2, #3              @ compare number of bytes with 3
    bls     memcpy_b            @ if less than or equal to 3 jump to copy bytes
    mov     r4, r0              @ temporary copy of destination address (because of AND syntax : Rd = Rd AND Rn)
    mov     r5, r1              @ temporary copy of source address (because of AND syntax : Rd = Rd AND Rn)
    mov     r6, #3              @ r6 = b11
    and     r4, r4, r6          @ r4 = r0 & b11 ; (number of bytes to the next destination aligned address)
    and     r5, r5, r6          @ r5 = r1 & b11 ; (number of bytes to the next source aligned address)
    add     r6, r4, r5          @ add the alignments of both destination and source
    cmp     r6, #0              @ compare result with 0
    beq     memcpy_w            @ if result is 0 then both destination and source are aligned
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
    beq     memcpy_b            @ jump to copy bytes until the end
    cmp     r6, #3              @ compare the result with 3
    beq     memcpy_b            @ jump to copy bytes until the end
    cmp     r5, #0              @ at this point r6 == 2, destination and source are at 2 byte offset
                                @ (r5 == 0) ? destination or source are aligned = copy 2 bytes
                                @ (r5 == 1) ? copy 1 byte to align destination and source at 2 bytes
    beq     memcpy_hw           @ r5 == 0 ; jump to copy halfwords
    ldrb    r4, [r1, r3]        @ r4 = [r1 + r3] ; (copy 8-bits from [r1 + r3] address to r4)
    strb    r4, [r0, r3]        @ [r0 + r3] = r4 ; (copy 8-bits from r4 to [r0 + r3] address)
    add     r3, r3, #1          @ increment offset
    b       memcpy_hw           @ destination and source are at 2 byte offset, jump to copy halfwords
memcpy_b:
    ldrb    r4, [r1, r3]        @ r4 = [r1 + r3] ; (copy 8-bits from [r1 + r3] address to r4)
    strb    r4, [r0, r3]        @ [r0 + r3] = r4 ; (copy 8-bits from r4 to [r0 + r3] address)
    add     r3, r3, #1          @ push offset forward by 8-bits
    cmp     r3, r2              @ check if there are more bytes left to copy
    bne     memcpy_b            @ repeat
    beq     memcpy_end          @ until no more bytes to copy
memcpy_hw:
    ldrh    r4, [r1, r3]        @ r4 = [r1 + r3] ; (copy 16-bits from [r1 + r3] address to r4)
    strh    r4, [r0, r3]        @ [r0 + r3] = r4 ; (copy 16-bits from r4 to [r0 + r3] address)
    add     r3, r3, #2          @ push offset forward by 16-bits
    sub     r6, r2, r3          @ get the number of bytes left to copy
    cmp     r6, #1              @ compare with 2
    bhi     memcpy_hw           @ if there are at least 2 bytes left to copy repeat copying 16-bits
    cmp     r6, #0              @ check if there are bytes left to copy
    beq     memcpy_end          @ if no more bytes to copy go straight to end
    b       memcpy_b            @ if not jump to copy 8-bits
memcpy_w:
    ldr     r4, [r1, r3]        @ r4 = [r1 + r3] ; (copy 32-bits from [r1 + r3] address to r4)
    str     r4, [r0, r3]        @ [r0 + r3] = r4 ; (copy 32-bits from r4 to [r0 + r3] address)
    add     r3, r3, #4          @ push offset forward by 32-bits
    sub     r6, r2, r3          @ get the number of bytes left to copy
    cmp     r6, #3              @ compare with 3
    bhi     memcpy_w            @ if there are at least 4 bytes left to copy repeat copying 32-bits
    cmp     r6, #0              @ check if there are bytes left to copy
    beq     memcpy_end          @ if no more bytes to copy go straight to end
    b       memcpy_b            @ if not jump to copy 8-bits
memcpy_end:
    pop     {r6}                @ restore preserved r6
    pop     {r5}                @ restore preserved r5
    pop     {r4}                @ restore preserved r4
    bx      lr                  @ return (pc = lr)
    .size   memcpy, . - memcpy


    @ Copy maximum <r1> bytes from <r3> bytes from address <r2> to address <r0>.
    @ Unlike memcpy it specifies the destionation buffer size to prevent overflow.
    @ r0 - destination buffer address
    @ r1 - destination buffer size
    @ r2 - source buffer address
    @ r3 - number of bytes to copy
    @ return r0 - TRUE if destination size was not exceeded, FALSE otherwise
    @ preserves all registers except r0, r1, r2, r3
    .global memcpy_s
    .type   memcpy_s, %function
memcpy_s:
    push    {lr}                @ preserve link register
    push    {r4}                @ preserve r4
    mov     r4, #1              @ r4 = 1 (initialize r4 with TRUE)
    cmp     r1, r3              @ compare destination size with number of bytes to copy
    bpl     memcpy_s_bpl        @ r1 >= r3 (prepare to call memcpy)
    mov     r3, r1              @ r3 = r1 (will copy maximum r1 bytes)
    mov     r4, #0              @ r4 = 0 (if number of bytes exceeds destination size, modify r4 to FALSE)
memcpy_s_bpl:
    mov     r1, r2              @ prepare <r1> parameter to call memcpy
    mov     r2, r3              @ prepare <r2> parameter to call memcpy
    bl      memcpy              @ jump to memcpy(<r0, <r1>, <r2>)
memcpy_s_end:
    mov     r0, r4              @ set return value to r0 (TRUE if destination size was not exceeded, FALSE otherwise)
    pop     {r4}                @ restore preserved r4
    pop     {pc}                @ restore preserved link register direclty into PC (bx lr not neede in this case)
    .size   memcpy_s, . - memcpy_s


    @ Copy <r2> bytes from address <r1> to address <r0>.
    @ Similar to memcpy but allows the destination and source to overlap.
    @ r0 - destination buffer address
    @ r1 - source buffer address
    @ r2 - number of bytes to copy
    @ return r0 - destination buffer address
    @ preserves all registers except r0
    .global memmove
    .type   memmove, %function
memmove:
    push    {r4}                @ preserve r4
    push    {r5}                @ preserve r5
    push    {r6}                @ preserve r6
    push    {r7}                @ preserve r7
    cmp     r2, #0              @ compare number of bytes with 0
    beq     memmove_end         @ if number of bytes is 0 go straight to end
    cmp     r0, r1              @ compare destination and source addresses
    beq     memmove_end         @ if destination = source go straight to end
    bmi     memmove_bmi         @ if destination < source    
    mov     r3, #255            @ r3 = 0xFF
    mov     r7, #255            @ r7 = 0xFF
    lsl     r7, r7, #8          @ r7 <<= 8 (r7 = 0xFF00)
    orr     r7, r3, r7          @ r7 |= r3 (r7 = 0xFFFF)
    lsl     r7, r7, #8          @ r7 <<= 8 (r7 = 0xFFFF00)
    orr     r7, r3, r7          @ r7 |= r3 (r7 = 0xFFFFFF)
    lsl     r7, r7, #8          @ r7 <<= 8 (r7 = 0xFFFFFF00)
    orr     r7, r3, r7          @ r7 |= r3 (r7 = 0xFFFFFFFF = -1)
    mov     r3, r2              @ set offset to number of bytes and decrement to 0
    b       memmove_align_diff
memmove_bmi:
    mov     r7, #1              @ r7 = 1
    mov     r3, #0              @ set offset to 0 and increment until equal to number of bytes
memmove_align_diff:
    cmp     r2, #3              @ compare number of bytes with 3
    bls     memmove_b           @ if less than or equal to 3 bytes to copy jump to copy bytes
    mov     r4, r0              @ temporary copy of destination address (because of AND syntax : Rd = Rd AND Rn)
    mov     r5, r1              @ temporary copy of source address (because of AND syntax : Rd = Rd AND Rn)
    mov     r6, #3              @ r6 = b11
    and     r4, r4, r6          @ r4 = r0 & b11 ; (number of bytes to the next destination aligned address)
    and     r5, r5, r6          @ r5 = r1 & b11 ; (number of bytes to the next source aligned address)
    add     r6, r4, r5          @ add the alignments of both destination and source
    cmp     r6, #0              @ compare result with 0
    beq     memmove_w_init      @ if result is 0 then both destination and source are aligned
                                @ jump to copy words
                                @ r2 >= 4 ; (at this point number of bytes to copy is greater than or equal to 4)
    sub     r6, r4, r5          @ alignment difference between destination and source
    bpl     memmove_not_aligned @ r4 >= r5 ; (jump for copy until the next aligned address)
    mov     r6, r4              @ r4 < r5 ; (switch their contents for later subtraction)
    mov     r4, r5
    mov     r5, r6
    sub     r6, r4, r5          @ get difference between alignment of destination and source
memmove_not_aligned:
    cmp     r6, #1              @ compare the result with 1
    beq     memmove_b           @ jump to copy bytes until the end
    cmp     r6, #3              @ compare the result with 3
    beq     memmove_b           @ jump to copy bytes until the end
    cmp     r5, #0              @ at this point r6 == 2, destination and source are at 2 byte offset
                                @ (r5 == 0) ? destination or source are aligned = copy 2 bytes
                                @ (r5 == 1) ? copy 1 byte to align destination and source at 2 bytes
    beq     memmove_hw_init     @ r5 == 0 ; jump to copy halfwords
    cmp     r7, #0
    bmi     memmove_not_aligned_bmi
    ldrb    r4, [r1, r3]        @ r4 = [r1 + r3] ; (copy 8-bits from [r1 + r3] address to r4)
    strb    r4, [r0, r3]        @ [r0 + r3] = r4 ; (copy 8-bits from r4 to [r0 + r3] address)
    add     r3, r3, r7          @ push offset forward (r7 = 1) or backward (r7 = -1) by 8-bits
    sub     r2, r2, #1          @
    b       memmove_hw_init     @ destination and source are at 2 byte offset, jump to copy halfwords
memmove_not_aligned_bmi:
    add     r3, r3, r7          @ push offset forward (r7 = 1) or backward (r7 = -1) by 8-bits
    ldrb    r4, [r1, r3]        @ r4 = [r1 + r3] ; (copy 8-bits from [r1 + r3] address to r4)
    strb    r4, [r0, r3]        @ [r0 + r3] = r4 ; (copy 8-bits from r4 to [r0 + r3] address)
    sub     r2, r2, #1          @
    b       memmove_hw_init     @ destination and source are at 2 byte offset, jump to copy halfwords
memmove_b_init:
    cmp     r7, #0
    bpl     memmove_b_init_bpl
    mov     r4, #255            @ r4 = 0xFF
    mov     r7, #255            @ r7 = 0xFF
    lsl     r7, r7, #8          @ r7 <<= 8 (r7 = 0xFF00)
    orr     r7, r4, r7          @ r7 |= r4 (r7 = 0xFFFF)
    lsl     r7, r7, #8          @ r7 <<= 8 (r7 = 0xFFFF00)
    orr     r7, r4, r7          @ r7 |= r4 (r7 = 0xFFFFFF)
    lsl     r7, r7, #8          @ r7 <<= 8 (r7 = 0xFFFFFF00)
    orr     r7, r4, r7          @ r7 |= r4 (r7 = 0xFFFFFFFF = -1)
    b       memmove_b
memmove_b_init_bpl:
    mov     r7, #1
memmove_b:
    cmp     r7, #0
    bmi     memmove_b_bmi
    ldrb    r4, [r1, r3]        @ r4 = [r1 + r3] ; (copy 8-bits from [r1 + r3] address to r4)
    strb    r4, [r0, r3]        @ [r0 + r3] = r4 ; (copy 8-bits from r4 to [r0 + r3] address)
    add     r3, r3, r7          @ push offset forward (r7 = 1) or backward (r7 = -1) by 8-bits
    sub     r2, r2, #1          @ subtract one byte from total number of bytes
    cmp     r2, #0              @ check if there are more bytes left to copy
    bhi     memmove_b           @ repeat
    b       memmove_end         @ until no more bytes to copy
memmove_b_bmi:
    add     r3, r3, r7          @ push offset forward (r7 = 1) or backward (r7 = -1) by 8-bits
    ldrb    r4, [r1, r3]        @ r4 = [r1 + r3] ; (copy 8-bits from [r1 + r3] address to r4)
    strb    r4, [r0, r3]        @ [r0 + r3] = r4 ; (copy 8-bits from r4 to [r0 + r3] address)
    sub     r2, r2, #1          @ subtract one byte from total number of bytes
    cmp     r2, #0              @ check if there are more bytes left to copy
    bhi     memmove_b           @ repeat
    b       memmove_end         @ until no more bytes to copy
memmove_hw_init:
    lsl     r7, r7, #1          @ r7 <<= 1 (r7 = 1 or r7 = -1)
memmove_hw:
    cmp     r7, #0
    bmi     memmove_hw_bmi
    ldrh    r4, [r1, r3]        @ r4 = [r1 + r3] ; (copy 16-bits from [r1 + r3] address to r4)
    strh    r4, [r0, r3]        @ [r0 + r3] = r4 ; (copy 16-bits from r4 to [r0 + r3] address)
    add     r3, r3, r7          @ push offset forward (r7 = 2) or backward (r7 = -2) by 16-bits
    sub     r2, r2, #2          @ subtract 2 bytes from total number of bytes
    cmp     r2, #1              @ compare number of bytes to set with 1
    bhi     memmove_hw          @ if there are at least 2 bytes left to copy repeat copying 16-bits
    cmp     r2, #0              @ check if there are more bytes left to copy
    bhi     memmove_b_init      @ 1 byte left, jump to copy 8-bits
    b       memmove_end         @ if no more bytes to copy go straight to end
memmove_hw_bmi:
    add     r3, r3, r7          @ push offset forward (r7 = 2) or backward (r7 = -2) by 16-bits
    ldrh    r4, [r1, r3]        @ r4 = [r1 + r3] ; (copy 16-bits from [r1 + r3] address to r4)
    strh    r4, [r0, r3]        @ [r0 + r3] = r4 ; (copy 16-bits from r4 to [r0 + r3] address)
    sub     r2, r2, #2          @ subtract 2 bytes from total number of bytes
    cmp     r2, #1              @ compare number of bytes to set with 1
    bhi     memmove_hw          @ if there are at least 2 bytes left to copy repeat copying 16-bits
    cmp     r2, #0              @ check if there are more bytes left to copy
    bhi     memmove_b_init      @ 1 byte left, jump to copy 8-bits
    b       memmove_end         @ if no more bytes to copy go straight to end
memmove_w_init:
    lsl     r7, r7, #2          @ r7 <<= 2 (r7 = 4 or r7 = -4)
memmove_w:
    cmp     r7, #0
    bmi     memmove_w_bmi
    ldr     r4, [r1, r3]        @ r4 = [r1 + r3] ; (copy 32-bits from [r1 + r3] address to r4)
    str     r4, [r0, r3]        @ [r0 + r3] = r4 ; (copy 32-bits from r4 to [r0 + r3] address)
    add     r3, r3, r7          @ push offset forward (r7 = 4) or backward (r7 = -4) by 32-bits
    sub     r2, r2, #4          @ subtract 4 bytes from total number of bytes
    cmp     r2, #3              @ compare number of bytes to set with 3
    bhi     memmove_w           @ if there are at least 4 bytes left to copy repeat copying 32-bits
    cmp     r2, #0              @ compare number of bytes to set with 0
    bhi     memmove_b_init      @ less than 4 bytes left, jump to copy 8-bits
    b       memmove_end         @ if no more bytes to copy go straight to end
memmove_w_bmi:
    add     r3, r3, r7          @ push offset forward (r7 = 4) or backward (r7 = -4) by 32-bits
    ldr     r4, [r1, r3]        @ r4 = [r1 + r3] ; (copy 32-bits from [r1 + r3] address to r4)
    str     r4, [r0, r3]        @ [r0 + r3] = r4 ; (copy 32-bits from r4 to [r0 + r3] address)
    sub     r2, r2, #4          @ subtract 4 bytes from total number of bytes
    cmp     r2, #3              @ compare number of bytes to set with 3
    bhi     memmove_w           @ if there are at least 4 bytes left to copy repeat copying 32-bits
    cmp     r2, #0              @ compare number of bytes to set with 0
    bhi     memmove_b_init      @ less than 4 bytes left, jump to copy 8-bits
memmove_end:
    pop     {r7}                @ restore preserved r7
    pop     {r6}                @ restore preserved r6
    pop     {r5}                @ restore preserved r5
    pop     {r4}                @ restore preserved r4
    bx      lr                  @ return (pc = lr)
    .size   memmove, . - memmove


    @ Compares the first <r2> bytes between address <r0> and address <r1>.
    @ r0 - first memory block address
    @ r1 - second memory block address
    @ r2 - number of bytes to compare
    @ return r0 - zero if they all match or a value different from zero
    @             representing which is greater if they do not.
    @ preserves all registers except r0, r3
    .global memcmp
    .type   memcmp, %function
memcmp:
    push    {r4}                @ preserve r4
    push    {r5}                @ preserve r5
    push    {r6}                @ preserve r6
    cmp     r2, #0              @ compare number of bytes with 0
    beq     memcmp_end          @ if number of bytes is 0 go straight to end
    mov     r3, #0              @ set offset to 0
    cmp     r2, #3              @ compare number of bytes with 3
    bls     memcmp_b            @ if less than or equal to 3 jump to compare bytes
    mov     r4, r0              @ temporary copy of destination address (because of AND syntax : Rd = Rd AND Rn)
    mov     r5, r1              @ temporary copy of source address (because of AND syntax : Rd = Rd AND Rn)
    mov     r6, #3              @ r6 = b11
    and     r4, r4, r6          @ r4 = r0 & b11 ; (number of bytes to the next destination aligned address)
    and     r5, r5, r6          @ r5 = r1 & b11 ; (number of bytes to the next source aligned address)
    add     r6, r4, r5          @ add the alignments of both destination and source
    cmp     r6, #0              @ compare result with 0
    beq     memcmp_w            @ if result is 0 then both destination and source are aligned
                                @ jump to compare words
                                @ r2 >= 4 ; (at this point number of bytes to compare is greater than or equal to 4)
    sub     r6, r4, r5          @ alignment difference between destination and source
    bpl     memcmp_not_aligned  @ r4 >= r5 ; (jump for compare until the next aligned address)
    mov     r6, r4              @ r4 < r5 ; (switch their contents for later subtraction)
    mov     r4, r5
    mov     r5, r6
    sub     r6, r4, r5          @ get difference between alignment of destination and source
memcmp_not_aligned:
    cmp     r6, #1              @ compare the result with 1
    beq     memcmp_b            @ jump to compare bytes until the end
    cmp     r6, #3              @ compare the result with 3
    beq     memcmp_b            @ jump to compare bytes until the end
    cmp     r5, #0              @ at this point r6 == 2, destination and source are at 2 byte offset
                                @ (r5 == 0) ? destination or source are aligned = compare 2 bytes
                                @ (r5 == 1) ? compare 1 byte to align destination and source at 2 bytes
    beq     memcmp_hw           @ r5 == 0 ; jump to compare halfwords
    ldrb    r4, [r0, r3]        @ r4 = [r0 + r3] ; (copy 8-bits from [r0 + r3] address to r4)
    ldrb    r5, [r1, r3]        @ r5 = [r0 + r3] ; (copy 8-bits from [r1 + r3] address to r5)
    sub     r6, r4, r5          @ get the difference
    cmp     r6, #0              @ to see if bytes are equal
    bne     memcmp_end          @ first different byte
    add     r3, r3, #1          @ increment offset
    b       memcmp_hw           @ destination and source are at 2 byte offset, jump to compare halfwords
memcmp_b:
    ldrb    r4, [r0, r3]        @ r4 = [r0 + r3] ; (copy 8-bits from [r0 + r3] address to r4)
    ldrb    r5, [r1, r3]        @ r5 = [r0 + r3] ; (copy 8-bits from [r1 + r3] address to r5)
    sub     r6, r4, r5          @ get the difference
    cmp     r6, #0              @ to see if 8-bits values are equal
    bne     memcmp_end          @ first different byte
    add     r3, r3, #1          @ push offset forward by 8-bits
    cmp     r3, r2              @ check if there are more bytes left to compare
    bne     memcmp_b            @ repeat
    beq     memcmp_end          @ until no more bytes to compare
memcmp_hw:
    ldrh    r4, [r0, r3]        @ r4 = [r0 + r3] ; (copy 16-bits from [r0 + r3] address to r4)
    ldrh    r5, [r1, r3]        @ r5 = [r0 + r3] ; (copy 16-bits from [r1 + r3] address to r5)
    sub     r6, r4, r5          @ get the difference
    cmp     r6, #0              @ to see if 16-bits values are equal
    bne     memcmp_diff         @ first different halfword
    add     r3, r3, #2          @ push offset forward by 16-bits
    sub     r6, r2, r3          @ get the number of bytes left to compare
    cmp     r6, #1              @ compare with 2
    bhi     memcmp_hw           @ if there are at least 2 bytes left to compare repeat comparing 16-bits
    cmp     r6, #0              @ check if there are bytes left to compare
    beq     memcmp_end          @ if no more bytes to compare go straight to end
    b       memcmp_b            @ if not jump to compare 8-bits
memcmp_w:
    ldr     r4, [r0, r3]        @ r4 = [r0 + r3] ; (copy 32-bits from [r0 + r3] address to r4)
    ldr     r5, [r1, r3]        @ r5 = [r0 + r3] ; (copy 32-bits from [r1 + r3] address to r5)
    sub     r6, r4, r5          @ get the difference
    cmp     r6, #0              @ to see if 32-bits values are equal
    bne     memcmp_diff         @ first different word
    add     r3, r3, #4          @ push offset forward by 32-bits
    sub     r6, r2, r3          @ get the number of bytes left to compare
    cmp     r6, #3              @ compare with 3
    bhi     memcmp_w            @ if there are at least 4 bytes left to compare repeat comparing 32-bits
    cmp     r6, #0              @ check if there are bytes left to compare
    beq     memcmp_end          @ if no more bytes to compare go straight to end
    b       memcmp_b            @ if not jump to compare 8-bits
memcmp_diff:
    mov     r3, #0              @ initialize offset for right shift
memcmp_diff_b:
    mov     r0, r4              @ copy (half)word r4 to r0
    mov     r1, r5              @ copy (half)word r5 to r1
    lsr     r0, r0, r3          @ right shift r0 with <r3> bytes
    lsr     r1, r1, r3          @ right shift r1 with <r3> bytes
    mov     r6, #255            @ set mask for AND
    and     r0, r0, r6          @ get LSB byte from r0
    and     r1, r1, r6          @ get LSB byte from r1
    add     r3, #8              @ update offset by 8-bits for right shift
    sub     r6, r0, r1          @ subtract r1 from r0
    cmp     r6, #0              @ and see if bytes are equal
    beq     memcmp_diff_b       @ repeat
memcmp_end:
    mov     r0, r6              @ restore return value in r0
    pop     {r6}                @ restore preserved r6
    pop     {r5}                @ restore preserved r5
    pop     {r4}                @ restore preserved r4
    bx      lr                  @ return (pc = lr)
    .size   memcmp, . - memcmp


    @ Gets the length of the C string pointed by <r0>.
    @ r0 - string pointer
    @ return r0 - length of the C string
    @ preserves all registers except r0, r1, r2
    .global strlen
    .type   strlen, %function
strlen:
    mov     r1, #0
strlen_non_zero:
    ldrb    r2, [r0, r1]        @ r2 = [r0 + r1] ; (copy 8-bits from [r0 + r3] address to r2)
    add     r1, #1              @ increment offset
    cmp     r2, #0              @ compare with NULL terminator char
    bne     strlen_non_zero     @ repeat
    sub     r1, r1, #1          @ do not count NULL terminator when found
    mov     r0, r1              @ copy return value (string length) to r0
    bx      lr                  @ return (pc = lr)
    .size   strlen, . - strlen
