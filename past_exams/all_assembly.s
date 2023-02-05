
                AREA    |.my_fancy_text|, CODE, READONLY
										; r0					r1							r2
;unsigned int media_pressioni_con_filtro(unsigned int VETT[], unsigned int numero_misure, unsigned int REMOVE)	
media_pressioni_con_filtro   PROC
                EXPORT media_pressioni_con_filtro   
				;; epilogue start			 
				STMFD sp!,{r4-r8,r10-r11,lr}
				;; epilogue end 
				;; calculate the indexes
				;; start index
				mov r4,#0
				add r4,r4,r2 
				;; end index 
				sub r1,r1,r2
				mov r7,#0
				mov r11,#0
				;; calculate total measurements in r8
				sub r8,r1,r4
loop			ldr r10, [r0]
				add r7,r7,r10
				;; update pointer 
				add r0,r0,#4 
				add r4,r4,#1
				cmp r8,r4
				bne loop 
				;; calculate average
				;; UNSIGNED DIVISION !
				udiv r0,r7,r8
				;;prologue start
				LDMFD sp!,{r4-r8,r10-r11,lr}
				mov pc,lr				 		
				;; prologue end 
                ENDP

				END

$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
				AREA asm_func, CODE, READONLY
				EXPORT count_bits_to_1

count_bits_to_1	MOV r12, sp
				STMFD sp!, {r4-r8, r10-r11, lr}
				
				MOV r5, #0
				MOV r7, #1
				MOV r8, #32
loop			TST r0, r7
				ADDNE r5, r5, #1
				LSL r7, r7, #1
				SUBS r8, r8, #1
				BNE loop				
				
				MOV r0, r5
				LDMFD sp!,{r4-r8,r10-r11,pc}
				
                END

$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$

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
					
$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$


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

$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$


monotono_crescente	push {r4-r8, lr}

check_monotonic		mov r3, #0 ; Initialize the loop counter to zero
					ldrb r2, [r0, r3] ; Load the first value from the array
					add r3, r3, #1 ; Increment the loop counter
					cmp r3, r1 ; Compare the loop counter with the size of the array
					bge done ; If it's equal or greater, branch to done

loop				ldrb r5, [r0, r3] ; Load the next value from the array
					cmp r5, r2 ; Compare it with the previous value
					bgt next ; If it's greater, branch to next
					mov r0, #0x55 ; Return 0x55 to indicate that the vector is not monotonic
					pop {r4-r8, pc} ; Restore r4 and pc from the stack

next				mov r2, r5 ; Save the current value as the previous value
					add r3, r3, #1 ; Increment the loop counter
					cmp r3, r1 ; Compare the loop counter with the size of the array
					blt loop ; If it's smaller, repeat the loop

done				mov r0, #0xFF ; Return 0xFF to indicate that the vector is monotonic
					pop {r4-r8, pc} ; Restore r4 and pc from the stack
					
				END

$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$


sum_odd_even	push {r2, r3, r4, lr} ; Save r2, r3, r4, and lr on the stack
				mov r2, #0 ; Initialize the sum of odd numbers to zero
				mov r3, #0 ; Initialize the sum of even numbers to zero
				mov r4, #0 ; Initialize the loop counter to zero

loop 			cmp r4, r1 ; Compare the loop counter with the length of the vector
			    bge done ; If it's equal or greater, branch to done
			    ldrb r0, [r0, r4] ; Load the current value from the vector
			    and r0, r0, #1 ; Check if it's odd or even
			    beq even ; If it's even, branch to even
			    add r2, r2, r0 ; Add the current value to the sum of odd numbers
			    b next ; Branch to next

even 			add r3, r3, r0 ; Add the current value to the sum of even numbers

next 			add r4, r4, #1 ; Increment the loop counter
    			b loop ; Repeat the loop

done 			mov r0, r2 ; Return the sum of odd numbers in r0
			    mov r1, r3 ; Return the sum of even numbers in r1
			    pop {r2, r3, r4, pc} ; Restore r2, r3, r4, and pc from the stack


$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$


sum_odd_even	push {r2, r3, r4, lr} ; Save r2, r3, r4, and lr on the stack
				mov r2, #0 ; Initialize the sum of odd numbers to zero
				mov r3, #0 ; Initialize the sum of even numbers to zero
				mov r4, #0 ; Initialize the loop counter to zero

loop 			cmp r4, r1 ; Compare the loop counter with the length of the vector
			    bge done ; If it's equal or greater, branch to done
			    ldrb r0, [r0, r4] ; Load the current value from the vector
			    and r0, r0, #1 ; Check if it's odd or even
			    beq even ; If it's even, branch to even
			    add r2, r2, r0 ; Add the current value to the sum of odd numbers
			    b next ; Branch to next

even 			add r3, r3, r0 ; Add the current value to the sum of even numbers

next 			add r4, r4, #1 ; Increment the loop counter
    			b loop ; Repeat the loop

done 			sub r0, r3, r2 ; Return the difference between the sum of even and odd numbers
				pop {r2, r3, r4, pc} ; Restore r2, r3, r4, and pc from the stack