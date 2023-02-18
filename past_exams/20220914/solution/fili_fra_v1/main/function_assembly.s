				AREA asm_func, CODE, READONLY
				EXPORT DIFF_POS_NEG

DIFF_POS_NEG 	PROC 
				STMFD sp!, {R4-R8, R10-R12, lr}

				MOV r4, #128 ; index of vector
				MOV r5, #0 ; count pos
				MOV r6, #0 ; count neg
				
loop_count		subs r4, r4, #1; decrement the chunk counter
				bmi eval_next; branch if negative
				
				ldr r8, [r0, r4]  ; load into r8 value of vector
				
				cmp r8, #0
				bgt count_pos
				b count_neg
				
count_pos		add r5, r5, #1
				b loop_count

count_neg		add r6, r6, #1
				b loop_count
				
eval_next		cmp r1, #128
				bgt set_overflow
				b finish
				
set_overflow	ldr r4,[r2]
				MOV r4, #1
				str r4,[r2]
				
finish			sub r0, r5, r6
							
				LDMFD sp!, {R4-R8, R10-R12, pc}
				ENDP
				END
