				AREA asm_func, CODE, READONLY
				EXPORT monotono_crescente

monotono_crescente	PROC
	STMFD sp!, {R4-R8, R10-R12, lr}
	MOV R4, #0 ;indice
	MOV R5, R1 ;fine ciclo
	MOV R6, #0
	MOV R7, #0
	MOV R8, #0
	MOV R9, #0
	MOV R10, #0

check_monotone 
	SUBS R5, R5, #1; sub from 
	
	