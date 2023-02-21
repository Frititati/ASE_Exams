				AREA asm_func, CODE, READONLY
				EXPORT funzione1

funzione1 	PROC 
			STMFD sp!, {R4-R8, R10-R12, lr}
			MOV R4, #0 ;indice
			MOV R5, #0 ;fine ciclo
			MOV R6, #0
			MOV R7, #0
			MOV R8, #0
			MOV R9, #0
			MOV R10, #0
			
			
			;azioni
			
			
			MOV R1, #0
			MOV R2, #0
			MOV R3, #0
			;azione per portare il valore in uscita in R0

			LDMFD sp!, {R4-R8, R10-R12, pc}
			ENDP
			END
