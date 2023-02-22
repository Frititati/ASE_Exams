				AREA asm_func, CODE, READONLY
				EXPORT monotono_crescente

monotono_crescente	PROC
					STMFD sp!, {R4-R8, R10-R12, lr}

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
					
					LDMFD sp!, {R4-R8, R10-R12, pc}
					ENDP
					END

###########################################################################################

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

##################################################################################

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
			MOV r10, r8
			STR r10, [r2]

			LDMFD sp!, {R4-R8, R10-R12, pc}
			ENDP
			END


#########################################################

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



####################################################################

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
					

################################################################


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



#########################################################

				AREA asm_func, CODE, READONLY
				EXPORT count_negative_and_odd

count_negative_and_odd 	PROC 
				STMFD sp!, {R4-R8, R10-R12, lr}
				MOV R4, r1 ;indice
				MOV r8, #0
				subs r10, r0, #4;  addr of vector into r6 such that we don't overwrite r0
				
loop			subs r4, r4, #1   ; decrement the chunk count
				bmi loop_done      ; exit the loop if we've processed all chunks
				
				ldr r5, [r10, #4]!;  load into r5 value of vector
				
				; check if number is negative
				CMP r5, #0 ; if less than we have neg
				BLT neg_number
				B loop
				
neg_number 		AND r6, r5, #1
				; check if number is odd
				CMP r6, #0; if 0 its even, if 1 its odd
				BNE odd_number
				B loop
				
odd_number		ADD r8, r8, #1
				B loop
								
loop_done		MOV r0, r8

				LDMFD sp!, {R4-R8, R10-R12, pc}
				ENDP
				END


#########################################################


				AREA asm_func, CODE, READONLY
				EXPORT get_and_sort

get_and_sort 	PROC 
				STMFD sp!, {R4-R8, R10-R12, lr}
				MOV R4, #0; indice vettore
				ADD r8, r2, #1; needed for second loop
				
first_loop		CMP r4, r2; compare current index with size of vett
				BGT end_first
				
				LDRB R5, [r0, r4]; load byte from array
				
				CMP r5, r1;  compare this to val
				ADDGT r4, r4, #1
				BGT first_loop
				B end_first
				
end_first		LDRB R5, [r0, r4]; load byte from array
				STRB R1, [r0, r4]; store byte from VAL
				
				
second_loop		CMP r4, r8; compare current index with size of vett + 1
				BEQ end_second
				
				ADD r7, r4, #1
				
				LDRB r6, [r0, r7]
				STRB r5, [r0, r7]
				MOV r5, r6
				ADD r4, r4, #1

				B second_loop
				
				
end_second		MOV r0, r1
				LDMFD sp!, {R4-R8, R10-R12, pc}
				ENDP
				END


#######################################################


				AREA asm_func, CODE, READONLY
				EXPORT count_bits_to_1

count_bits_to_1	PROC
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


####################################################



				AREA asm_func, CODE, READONLY
				EXPORT calcola_somma_prodotto

calcola_somma_prodotto	PROC
				STMFD sp!, {r4-r8, r10-r11, lr}

				SUBS r10, r0, #4; addrss of starting vector
				MOV r4, r1; index of vector

				MOV r7, #0;

loop 			SUBS r4, r4, #2; subtract 2 from the index of the vector
				BMI end_loop

				LDR r5, [r10, #4]!; vector p1
				LDR r6, [r10, #4]!; vector p2

				MUL r8, r5, r6; mul p1xp2

				ADD r7, r7, r8;
				B loop

end_loop 		CMP r7, #255
				MOVGE r5, #-1;
				MOVLT r5, #1;
				STRB r5, [r2]

				MOV r0, r7;
				LDMFD sp!,{r4-r8,r10-r11,pc}
				
                END


