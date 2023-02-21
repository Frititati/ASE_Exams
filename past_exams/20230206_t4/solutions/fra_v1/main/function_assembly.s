				AREA asm_func, CODE, READONLY
				EXPORT media_e_superiori_alla_media

media_e_superiori_alla_media 	PROC 
								STMFD sp!, {R4-R8, R10-R12, lr}
								
								MOV r4, #0 ; num iterazioni
								SUB r5, r0, #1 ; base address
								MOV r6, #0 ; somma vettore
								MOV r10, #0 ; count superiori alla media
								
loop							CMP r4, r1
								BEQ fine_primo_loop
								LDRB r7, [r5, #1]! ; carico il valore
								ADD r6, r6, r7 ; aggiungo alla somma
								ADD r4, r4, #1 ; aggiorno il count delle iterazioni
								B loop
								
fine_primo_loop					UDIV r8, r6, r1
								MOV r4, #0 ; reset num iterazioni
								SUBS r5, r0, #1 ; reset base address
								
secondo_loop					CMP r4, r1 
								BEQ fine_secondo_loop
								LDRB r7, [r5, #1]! ; carico il valore
								CMP r7, r8
								BGT superiore
								ADD r4, r4, #1 ; aggiorno il count delle iterazioni
								B secondo_loop
								
superiore						ADD r10, r10, #1 ; aggiorno il counter
								ADD r4, r4, #1
								B secondo_loop
								
fine_secondo_loop				MOV r0, r8
								LDRB r4, [r2]
								MOV r4, r10
								STR r4, [r2]
								LDMFD sp!, {R4-R8, R10-R12, pc}
								ENDP
								END
