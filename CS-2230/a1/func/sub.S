	.file "sub.S"
	.text
.global sub
sub:
	sub r14, r15  ; subtracts the value in r14 from r15 & stores ans in r15
	ret           ; returns the answer

