				AREA asm_func, CODE, READONLY
				EXPORT divisible

divisible 	PROC 
			STMFD sp!, {R4-R8, R10-R12, lr}
			
			udiv r4, r0, r1
			mul r5, r4, r1
			sub r6, r0, r5
			cmp r6, #0
			MOVEQ r0, #0
			MOVNE r0, r6
			
			LDMFD sp!, {R4-R8, R10-R12, pc}
			ENDP
			END
