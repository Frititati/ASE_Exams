
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