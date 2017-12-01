	.file "mul.S"
	.text
.global mul
mul:
	
	add r15, r12  ; Adds r15 to r12 & stores the answer in r12
	dec r14       ; Decrements r14 to loop until 0
	cmp #0, r14   ; Compares value in r14 to the number zero
	jnz mul       ; Jumps if not zero 
	mov r12, r15  ; Moves the value from r12 to r15
	ret           ; Returns the value now stored in r15

