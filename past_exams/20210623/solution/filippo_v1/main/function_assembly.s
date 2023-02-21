				AREA asm_func, CODE, READONLY
				EXPORT sopra_la_media

sopra_la_media	PROC
				
				STMFD sp!, {R4-R8, R10-R12, lr}
				
				SUB r10, r0, #1; get address of vett removing first entry
				MOV r4, r1; index
				MOV r6, #0; sum of array
				MOV r8, #0;
				
loop_sum		SUBS r4, r4, #1
				BMI sum_done
				
				LDRB r5, [r10, #1]!; get value of char in vett and update address
				
				ADD r6, r6, r5; add to r6 the value of vector
				B loop_sum
				
sum_done		UDIV r7, r6, r1; mean
				MOV r4, r1; reset index
				SUB r10, r0, #1; get address of vett removing first entry
				
loop_over		SUBS r4, r4, #1;
				BMI over_done
				
				LDRB r5, [r10, #1]!; get value of char in vett and update address
				
				CMP r5, r7; if gt add to counter
				BGT over_count
				B loop_over
				
over_count		ADD r8, r8, #1; add 1 to count
				B loop_over
				
over_done		MOV r0, r8;

				LDMFD sp!, {R4-R8, R10-R12, pc}
				
				END
					

