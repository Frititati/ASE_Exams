				AREA asm_func, CODE, READONLY
				EXPORT duty_cycle

duty_cycle 		PROC 
				STMFD sp!, {R4-R8, R10-R12, lr}

				MOV r4, r3 ; index of vector
				MOV r5, #0 ; sum even
				MOV r6, #0 ; sum odd
				
loop_count		subs r4, r4, #1; decrement the chunk counter
				bmi eval_duty; branch if negative
				
				ldr r8, [r2, r4]  ; load into r8 value of vector
				
				and r7, r4, #1 ; bitwise AND the argument with 1
				cmp r7, #0
				beq sum_even
				b sum_odd
				
sum_even		ADD r5, r5, r8; add to even sum
				b loop_count
				
sum_odd			ADD r6, r6, r8; add to odd sum
				b loop_count

eval_duty		cmp r0, #0
				beq start_0
				b start_1
				
start_0			MOV r11, #100
				mul r5, r5, r11
				udiv r4, r5, r1
				b end_proc

start_1			MOV r11, #100
				mul r6, r6, r11
				udiv r4, r6, r1
	
end_proc		MOV r0, r4
	
				LDMFD sp!, {R4-R8, R10-R12, pc}
				ENDP
				END
