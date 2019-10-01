	AREA MyData, CODE
	
array1
	DCD 0x87654321, 0x23456789, 0x3456789A
array2
	DCD 0xAABBCCDD, 0x7FCCDDEE, 0xCCDDEEFF
	
	AREA MyAnswers, DATA
array3
	SPACE 12


	AREA MyCode, CODE, READONLY
	EXPORT	__main
	EXPORT mySystemInit

mySystemInit
	BX LR

__main
	ENTRY
	LDR R0, =array1
	LDR R1, =array2
	LDR R2, =array3
	
	LDR R3, [R0], #4
	LDR R4, [R1], #4
	ADDS R4, R3, R4
	STR R4, [R2], #4
	
	LDR R3, [R0], #4
	LDR R4, [R1], #4
	ADDS R4, R3, R4
	STR R4, [R2], #4	
	
	LDR R3, [R0]
	LDR R4, [R1]
	ADDS R4, R3, R4
	STR R4, [R2]	
	
	LDR R0, =0x22000000
	LDR R1, =32
	
loop
	LDR R2, [R0], #4
	SUBS R1, #1
	BNE loop
	
	B	.
	END
