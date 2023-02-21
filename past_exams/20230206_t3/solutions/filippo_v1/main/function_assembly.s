				AREA asm_func, CODE, READONLY
				EXPORT differenza_media_positivi_negativi

differenza_media_positivi_negativi 	PROC 
			STMFD sp!, {R4-R8, R10-R12, lr}
			SUBS r10, r0, #4;
			MOV r4, r1;
			MOV r8, #0;
			MOV r6, #0; sum of neg
			MOV r7, #0; count of neg
			MOV r11, #0; sum of pos
			MOV r12, #0; count of pos

loop		SUBS r4, r4, #1;
			BMI loop_done
			
			LDR r5, [r10, #4]!; load into r5
			
			CMP r5, #0; GT pos, LT neg
			BGT val_pos
			BLT val_neg
			B loop
			
val_pos		ADD r12, r12, #1;
			ADDS r11, r11, r5;
			BVS has_over
			B loop


val_neg		ADD r6, r6, #1;
			ADDS r7, r7, r5;
			BVS has_over
			B loop

has_over	MOV r8, #0xFF;
			B loop

loop_done	SDIV r4, r11, r12; positive mean
			SDIV r5, r6, r7; negative mean
			
			SUB r0, r4, r5; pos-neg means
			
			LDR r10, [r2]
			MOV r10, #0xFF
			STR r10, [r2]

			LDMFD sp!, {R4-R8, R10-R12, pc}
			ENDP
			END
