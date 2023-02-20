				AREA asm_func, CODE, READONLY
				EXPORT media_e_superiori_alla_media

media_e_superiori_alla_media 	PROC 
			STMFD sp!, {R4-R8, R10-R12, lr}
			SUB r10, r0, #1; copy memory addr of vett into r10
			MOV r4, r1; size of array
			MOV r6, #0; sum of array
			MOV r8, #0; sum of over
			
			
loop_sum	SUBS r4, r4, #1; -1 from size
			BMI sum_done
			
			LDRB r5, [r10, #1]!; load into r5 value of vector
			ADD r6, r6, r5; add to sum
			B loop_sum
			
sum_done	UDIV r7, r6, r1; mean of array into r7
			SUB r10, r0, #1; copy memory addr of vett into r10
			MOV r4, r1; size of array
			
loop_over	SUBS r4, r4, #1; -1 from size
			BMI over_done
			
			LDRB r5, [r10, #1]!; load into r5 value of vector
			CMP r5, r7; if GT its over
			BGT count_over
			B loop_over
			
count_over	ADD r8, r8, #1;
			B loop_over
			
over_done	LDRB r9, [r2]; load r2 addr in r9
			MOV r9, r8
			STRB r9, [r2]; store over in r9
			
			MOV r0, r7

			LDMFD sp!, {R4-R8, R10-R12, pc}
			ENDP
			END
