
	AREA MyData, DATA
	
	AREA MyCode, CODE, READONLY
	EXPORT	__main
	EXPORT mySystemInit
	IMPORT addstack

mySystemInit
	BX LR


__main
	ENTRY
	;Move the address for storing into R0
	MOVW R0, #0x1000
	MOVT R0, #0x2000

	;Move first item of the first array into R1
	MOVW R1, #0x4321
	MOVT R1, #0x8765
	;Store R1 into the location held by R0
	STR R1, [R0], #4
	
	;Move second item of the first array into R2
	MOVW R2, #0x6789
	MOVT R2, #0x2345
	
	STR R2, [R0], #4
	
	;Move third item of the first array into R3
	MOVW R3, #0x789A
	MOVT R3, #0x3456
	
	STR R3, [R0], #4
	
	;Move the address for storing into R0
	MOVW R0, #0x1050
	MOVT R0, #0x2000

	;Move first item of the second array into R1
	MOVW R1, #0xCCDD
	MOVT R1, #0xAABB
	;Store R1 into the location held by R0
	STR R1, [R0], #4
	
	;Move second item of the second array into R2
	MOVW R2, #0xDDEE
	MOVT R2, #0x7FCC
	
	STR R2, [R0], #4
	
	;Move third item of the second array into R3
	MOVW R3, #0xEEFF
	MOVT R3, #0xCCDD
	
	STR R3, [R0], #4
	
	BL addstack
	
	B .
	END
		
;	AREA MyData, DATA
	
;array1
;	DCD 0x87654321, 0x23456789, 0x3456789A
;array2
;	DCD 0xAABBCCDD, 0x7FCCDDEE, 0xCCDDEEFF
	
;	AREA MyAnswers, DATA
;array3
;	SPACE 12


;	AREA MyCode, CODE, READONLY
;	EXPORT	__main
;	EXPORT mySystemInit
;
;mySystemInit
;	BX LR

;__main
;	ENTRY
;	LDR R0, =array1
;	LDR R1, =array2
;	LDR R2, =array3
;	
;	LDR R3, [R0], #4
;	LDR R4, [R1], #4
;	ADDS R4, R3, R4
;	STR R4, [R2], #4
;	
;	LDR R3, [R0], #4
;	LDR R4, [R1], #4
;	ADDS R4, R3, R4
;	STR R4, [R2], #4	
;	
;	LDR R3, [R0]
;	LDR R4, [R1]
;	ADDS R4, R3, R4
;	STR R4, [R2]	

;	Removed after part 4
;	LDR R0, =0x22000000
;	LDR R1, =32
	
;loop
;	LDR R2, [R0], #4
;	SUBS R1, #1
;	BNE loop
	
;	B	.
;	END