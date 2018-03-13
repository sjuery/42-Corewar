.name "champtest"
.comment "load into register, register into memory"
	
	ld	%42, r2
	st	r2, 34
	ldi	r1, %84, r2
	st	r1, 42
