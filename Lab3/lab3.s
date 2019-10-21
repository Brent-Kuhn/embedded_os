	AREA Asm, CODE
	EXPORT findLowBitASM
	EXPORT mySystemInit
		
mySystemInit
	BX LR
	
findLowBitASM
	MOV R10, #0		; Load 0 for the current position
	MOV R3, #8		; Load 8 for counting through array elements
	MOV R12, R0		; Save R0 value into R12
L1
		LDR R4, [R0]		; Load the value of R4 with the value from address R0 (where the pointer from the array is sitting)
		MOV R2, #32		; Load 32 for iterating through all 32 bits in each element
L2
			AND R5, R4, #0x00001	; And 0x0001 and the current value to check and see if equal to 1
			CMP R5, #0x0001			; Compare R5 with 0x0001 if it is one, then we found our item
			LSL R4, R4, #1			; Left shift once in prep for next check
			BEQ EXIT				; Leave the function and return the value
			ADD R10, R10, #1		; Increase the position counter
			SUBS R2, R2, #1			; Loop1 counter
			BNE L2					; Else move to the next bit in that bad boy
			SUBS R3, R6, #1			; If this value is zero, we have been through all elements in the array
			BEQ EXIT
			ADD R0, R0, #4			; Move to the next elememt (Size may be wrong)
			B L1
			
	
EXIT
	MOV R0, R12
	; Need to figure out how to return the location value
	END