	.file "divd.S"
	.text
.global divd
divd:
    cmp #0, r14;    Compares register 14 to 0 to determine if it is trying to divide by zero
    jz zero;        Jumps to section zero

    mov #0, r12;    Puts the value 0 to register 12
    cmp #0, r15;    Compares the value in register 15 to 0 tp check if the first value is positive or negative
    jl divdn;       If register 15 is less than 0, jump to divdn
    jge divdp;      If register 15 is greater than or equal to 0, jump to divdp    
	ret

zero:
    mov #0, r15;    Just returns 0 if it is trying to divide by zero
    ret

divdp:
    cmp #0, r14;    Compares register 14 to 0 to determine if the second value is positive or negative
    jl divdpn;      If the first value is positive and the second is negative, jump to divdpn
    jge divdpp;     If the first and second values are positive, jump to divpp
    ret

divdn:
    cmp #0, r14;    Compares register 14 to 0 to determine if the second value is positive or negative
    jl divdnn;      If the first and second values are negative, jump to divdnn
    jge divdnp;     If the first value is negative and the second is positive, jump to divdnp  
    ret

divdpn:
    add r14, r15;   Adds the value of register 14 to register 15
    dec r12;        Decrements the value of register 12 by one
    cmp #0, r15;    Compares the value of register 15 to 0
    jge divdpn;     Jump back to the start of divdpn if register 15 is greater than or equal to 0.
    inc r12;        Increment register 12 by 1 after the loop ends
    mov r12, r15;   Moves the value of register 12 back to register 15
    ret

divdnn:
    sub r14, r15;   Subtracts the value of register 14 from register 15
    inc r12;        Increments the value of register 12 by one
    cmp #1, r15;    Compares the value of r15 to 1
    jl divdnn;      If register 15 is less than 1, jump to divdnn
    dec r12;        Decrement register 12 by 1 after the loop ends
    mov r12, r15;   Moves the value of register 12 to register 15
    ret

divdnp:
    add r14, r15;   Adds the value of register 14 to register 15
    dec r12;        Decrement register 12 by one
    cmp #1, r15;    Compares the value of register 15 to 1
    jl divdnp;      Jump to divdnp if register 15 is less than 1
    inc r12;        Increment register 12 by 1 after the loop ends
    mov r12, r15;   Moves the value of register 12 to register 15
    ret

divdpp:
    sub r14, r15;   Subtracts the value of register 14 from register 15
    inc r12;        Increments the value of register 12 by 1
    cmp #0, r15;    Compares the value of register 15 to 0
    jge divdpp;      If the value of register 15 is greater than or equal to 0, jump to divdpp
    dec r12;        Decrement register 12 by 1
    mov r12, r15;   Moves the value fo regsiter 12 to register 15  
    ret

