	.file "add.S"
	.text
.global add
add:
	add r14, r15  ; adds the value in r14 to r15 then stores the new value in r15
	ret           ; returns the answer

