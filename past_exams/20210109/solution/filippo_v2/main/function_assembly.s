				AREA asm_func, CODE, READONLY
				EXPORT count_negative_and_odd

count_negative_and_odd 	PROC 
				STMFD sp!, {R4-R8, R10-R12, lr}
				MOV R4, r1 ;indice
				MOV r8, #0
				subs r10, r0, #4;  addr of vector into r6 such that we don't overwrite r0
				
loop			subs r4, r4, #1   ; decrement the chunk count
				bmi loop_done      ; exit the loop if we've processed all chunks
				
				ldr r5, [r10, #4]!;  load into r5 value of vector
				
				; check if number is negative
				CMP r5, #0 ; if less than we have neg
				BLT neg_number
				B loop
				
neg_number 		AND r6, r5, #1
				; check if number is odd
				CMP r6, #0; if 0 its even, if 1 its odd
				BNE odd_number
				B loop
				
odd_number		ADD r8, r8, #1
				B loop
								
loop_done		MOV r0, r8

				LDMFD sp!, {R4-R8, R10-R12, pc}
				ENDP
				END
