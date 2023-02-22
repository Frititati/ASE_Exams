				AREA asm_func, CODE, READONLY
				EXPORT DIFF_POS_NEG
					
DIFF_POS_NEG 	PROC 
			STMFD sp!, {R4-R8, R10-R12, lr}
			SUB r10, r0, #4; load into r10 memory address of r0 but taking 4 bytes for the first offset
			MOV r4, r1;
			MOV r6, #0; sum of positive
			MOV r7, #0; sum of negative
			
			MOV r8, #0;
			
loop		SUBS r4, r4, #1;
			BMI end_loop
			
			LDR r5, [r10, #4]!; load into r5 the value of vett
			
			CMP r5, #0; GE means positive, LT means negative
			BGE pos_number
			BLT neg_number
			
pos_number	ADDS r6, r6, r5; add to pos sum
			BVS has_over
			B loop
			
neg_number	ADDS r7, r7, r5; add to neg sum
			BVS has_over
			B loop

has_over	MOV r8, #1;
			B loop
			
end_loop	ADD r0, r6, r7; difference between pos and neg

			LDRB r5, [r2]
			MOV r5, r8;
			STRB r5, [r2]; add the overflow to overflow refence
			
			LDMFD sp!, {R4-R8, R10-R12, pc}
			ENDP
			END
				
				AREA asm_func, CODE, READONLY
				EXPORT DIFF_POS_NEG2

DIFF_POS_NEG2 	PROC 
			STMFD sp!, {R4-R8, R10-R12, lr}
			MOV R3,#0;NEG
			MOV R4,#0;POS
			MOV R5,#0
			MOV R7,#1
			LSL R7,R7,#31
CICLO		LDR R6,[R0]
			TST R6,R7
			BEQ qua
			ADDNES R3,R3,R6
			MOVVS R8,#1
			STRBVS R8,[R2]
			

qua			ADDEQS R4,R4,R6
			MOVVS R8,#1
			STRBVS R8,[R2]
			ADD R5,R5,#1
			CMP R5,R1
			BNE CICLO
			SUB R0,R3,R4
			
			LDMFD sp!, {R4-R8, R10-R12, pc}
			ENDP
			END