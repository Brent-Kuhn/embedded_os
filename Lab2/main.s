	AREA MyData, DATA
	
	AREA MyCode, CODE, READONLY
		EXPORT addstack
addstack
	;Move the address for the first array into R0
	MOVW R0, #0x1000
	MOVT R0, #0x2000
	
	;Move the address for second array into R1
	MOVW R1, #0x1050
	MOVT R1, #0x2000
	
	;Move the address for addition array into R2
	MOVW R2, #0x1100
	MOVT R2, #0x2000
	
	LDR R5, =3
	
loop
	
	LDR R3, [R0], #4
	LDR R4, [R1], #4
	ADDS R4, R3, R4
	STR R4, [R2], #4
	SUBS R5, #1
	BNE loop

	
	NOP
	B .	
	END