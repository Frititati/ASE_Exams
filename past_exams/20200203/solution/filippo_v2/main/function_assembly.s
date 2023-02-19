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
