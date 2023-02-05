				AREA asm_func, CODE, READONLY
				EXPORT count_negative_and_odd

count_negative_and_odd	push {r4-r8, lr}

				mov r5, #0;  set value of counter to 0
				mov r7, r1;  set value of pointer to array size
				SUBS r0, r0, #4; sub 4 from r0
				mov r6, r0;  addr of vector into r6 such that we don't overwrite r0
				
loop_count      subs r7, r7, #1; decrement the chunk counter
				bmi loop_count_done;
				
				ldr r4, [r6, #4]!;  load into r3 value of vector
				
				; first part is for odd check
				and r3, r4, #1 ; bitwise AND the argument with 1
				cmp r3, #0   ; compare the result with 0
				bne check_negative
				b loop_count; restart loop

check_negative	asr r3, r4, #31 ; arithmetic shift right the argument 31 bits
				and r3, r3, #1 ; bitwise AND the result with 1
				cmp r3, #0   ; compare the result with 0
				addne r5, r5, #1; increment counter is its negative
				b loop_count; restart loop
				
loop_count_done	mov r0, r5   ; return the count in r0
				pop {r4-r8, pc} ; restore the saved registers and return
				
				END
					
					
					
;count_negative_and_odd	push {r4-r8, lr}
;
;				mov r5, #0;  set value of counter to 0
;				mov r7, r1;  set value of pointer to array size
;				mov r6, r0;  addr of vector into r6 such that we don't overwrite r0
;				
;loop_count      subs r7, r7, #1; decrement the chunk counter
;				bmi loop_count_done;
;				
;				ldr r4, [r6, #4]!;  load into r3 value of vector
;				; first part is for odd check
;				and r3, r4, #1 ; bitwise AND the argument with 1
;				cmp r3, #0   ; compare the result with 0
;				addne r5, r5, #1; increment counter is its odd
;				b loop_count; restart loop
;				
;loop_count_done		mov r7, r2;  set value of pointer to array size
;					mov r6, r0;  addr of vector into r6 such that we don't overwrite r0
;
;loop_negative   subs r7, r7, #1; decrement the chunk counter
;				bmi loop_negative_done;
;				
;				ldr r4, [r6, #4]!;  load into r3 value of vector
;				; first part is for negative check
;				asr r4, r4, #31 ; arithmetic shift right the argument 31 bits
;				and r3, r4, #1 ; bitwise AND the result with 1
;				cmp r3, #0   ; compare the result with 0
;				addne r5, r5, #1; increment counter is its negative
;				b loop_negative; restart loop
;				
;loop_negative_done	mov r0, r5   ; return the count in r0
;				pop {r4-r8, pc} ; restore the saved registers and return
;				
;				END;
