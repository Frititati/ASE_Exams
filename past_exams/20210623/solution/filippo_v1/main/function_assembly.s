				AREA asm_func, CODE, READONLY
				EXPORT sopra_la_media

sopra_la_media	push {r4-r8, lr}
				
				mov r4, r0   ; r0 contains the pointer to the array
				mov r5, #0   ; initialize the sum to 0
				mov r6, r1   ; move the length of the array into r6

				ldr r7, [r0, #4]  ; load the length of the array into r7
				add r7, r7, #1    ; add 1 to account for the length word
				lsrs r7, r7, #2   ; divide the length by 4 to get the number of word-sized chunks

sum_loop		subs r7, r7, #1   ; decrement the chunk count
				bmi sum_done      ; exit the loop if we've processed all chunks

				ldmia r4!, {r0-r3} ; load 4 elements into r0-r3
				add r5, r5, r0    ; add r0 to the sum
				add r5, r5, r1    ; add r1 to the sum
				add r5, r5, r2    ; add r2 to the sum
				add r5, r5, r3    ; add r3 to the sum
				b sum_loop        ; repeat the loop

sum_done		mov r7, r5   ; move the sum into r7
				mov r5, #0   ; initialize the count to 0
				ldr r8, [r0, #0]  ; load the first element into r8
				
				mov r0, r7   ; move the sum into r0
				mov r1, r6   ; move the length of the array into r1

divide_loop		subs r1, r1, #1   ; decrement the divisor by 1
				bmi divide_done   ; exit the loop if we've divided by the length

				sub r0, r0, r7    ; subtract the sum from the dividend
				b divide_loop     ; repeat the loop

divide_done		mov r7, r0   ; move the average into r7

				add r4, r4, r6   ; add the length of the array to the pointer to get to the end of the array
				subs r6, r6, #1  ; decrement the length by 1

count_loop		subs r6, r6, #1   ; decrement the index
				bmi count_done    ; exit the loop if we've processed all elements

				ldr r8, [r4, #-1]! ; load the next element into r8
				cmp r8, r7    ; compare the element with the average
				bgt count_inc ; if the element is greater, increment the count
				b count_loop  ; repeat the loop

count_inc		adds r5, r5, #1 ; increment the count
				b count_loop   ; repeat the loop

count_done		mov r0, r5   ; return the count in r0
				pop {r4-r8, pc} ; restore the saved registers and return
				
				END
