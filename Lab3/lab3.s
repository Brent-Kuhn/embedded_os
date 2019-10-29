	AREA Asm, CODE
	EXPORT findLowBitASM
	
findLowBitASM
	MOV R10, #0		; Load 0 for the current position

	MOV R12, R0		; Save R0 value into R12
L1
		LDR R4, [R0]		; Load the value of R4 with the value from address R0 (where the pointer from the array is sitting)
		MOV R7, #32			; Load 32 for iterating through all 32 bits in each element
L2
			AND R9, R4, #0x000000001	; And 0x00000001 and the current value to check and see if equal to 1
			CMP R9, #0x00000001			; Compare R9 with 0x00000001 if it is one, then we found our item
			BEQ EXIT				; Leave the function and return the value
			LSR R4, R4, #1			; Left shift once in prep for next check
			ADD R10, R10, #1		; Increase the position counter
			SUBS R7, R7, #1			; Loop1 counter
			BNE L2					; Else move to the next bit in that bad boy
			ADD R0, R0, #1			; Move to the next elememt (Size may be wrong)
			B L1
			
	
EXIT
	MOV R0, R10

	; Need to figure out how to return the location value
	BX LR
	END