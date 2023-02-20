				AREA asm_func, CODE, READONLY
				EXPORT differenza_media_positivi_negativi

differenza_media_positivi_negativi 	PROC 
			STMFD sp!, {R4-R8, R10-R12, lr}
			
			SUB r10, r0, #4; save starting address
			MOV r4, r1;
			MOV r6, #0; neg counter
			MOV r7, #0; pos counter
			MOV r8, #0; neg sum
			MOV r11, #0; pos sum
			MOV r12, #0; overflow flag
			
loop		SUBS r4, r4, #1;
			BMI loop_end
			
			LDR r5, [r10, #4]! ; load value of array into r5
			
			CMP r5, #0 ; if LT it negative, else positive
			BLT is_neg
			B is_pos
			
is_neg		ADD r6, r6, #1;
			ADDS r8, r8, r5;
			BVS has_over
			B loop

is_pos 		ADD r7, r7, #1;
			ADD r11, r11, r5;
			BVS has_over
			B loop
			
has_over 	MOV r12, #0xFF;
			B loop
			
loop_end    SDIV r5, r8, r6; save into r5 the negative mean
			MOV r6, r5; move mean neg into r6
			SDIV r5, r11, r7; save into r5 the positive mean
			MOV r7, r5; move mean pos into r7
			
			SUB r0, r7, r6; sub into r0 the pos - negative mean
			
			LDR r4, [r2]
			MOV r4, r12
			str r4,[r2]
			
			LDMFD sp!, {R4-R8, R10-R12, pc}
			ENDP
			END
