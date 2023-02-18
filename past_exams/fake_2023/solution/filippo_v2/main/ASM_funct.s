				AREA	my_code, CODE, READONLY
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
		
;COSE UTILI		
		
;funzioni utili ARM ASSEMBLY
;Programmazione Condizionale S dopo istruzione,
;EQ-> Z=1, NE-> Z=0, GE-> >=, GT-> >, LT-> <, LE-> <=, MI-> <0
;CMP tra due numeri per fare la compare
;TST AND logico?
;TEQ TestEquivalence
;il secondo operando deve essere 0x00XY00XY, 0xXY00XY00,0xXYXYXYXY o costante ottenuta come shift left di valore 8bit

;ALUinstr
;MRS specReg to REG, MSR REG to specReg, APSR Flag Register

;ADD 3 registri, ADC Aggiungiamo col carry e possibile fare 64 bit
;SUB 3 registri, SBC ""
;MUL 3 registri, UMULL 4 registri unsigned 64bit, SMULL 4 registri signed 64bit
;MLA 4 registri moltiplicazione cumulativa 1=2*3+4
;UDIV 3 registri unsigned, SDIV 3 registri signed, non possiamo mettere s

;AND bit a bit, BIC = AND NOT, ORR = OR, EOR= XOR, ORN = OR NOT, MVN = NOT, tutti 3 reg
;LSL, LSR shift fisici 3 registri, ASR shift right logico senza cambiare segno

;LiteralPools
;LDR Reg, costante oppure registro e offset possibile con pre o post increment
;preincrement [Rx, #4], se postpongo ! si aggiorna il registro
;postincrement [Rx], #4
;LDR 32 byte, LDRB 8, LDRH 16, LDRSB signed byte, LDRSH '', LDRD 64 byte
;STR 32 byte, STRB ", STRH " , no               , no      , STRD 64 byte

;Branch
;B label, BX indirect, BL con link, BLX indirect con link

;Stack
;STMFD=PUSH, LDMFD=POP, intercambiabili. Preferito Full Descending

;già implementate nel sample.c funzioni per gestire lo stack modalità thread o no per svc

;ricordarsi che per C volatile per quelle variabili che entrano qui dentro. Chissà cosa succede :/

;EXPORT per far vedere la funzione fuori, IMPORT per vedere da altri file, extern per leggere da altri file


;FLAG N=1 BIT31=1, Z=1 se Res=0, Carry=1 risultato >32 bit oppure dopo shift '1' era già nel carry, V=1 numero più grande di 31 bit
		
		
;-----------------------------------------------------------		
		
		
;azioni prima del ciclo. Indici e cose
	
;	MOV R9, x in base alla grandezza del vettore. 4 = 32 byte
;	MUL R9, R9, R2 ;presupponendo che ci sia valore offset in R2
;	ADD R0, R0, R9 ;presuppondendo che ci sia indirizzo vettore in R0
;   MOV R9, 0


;indice dovrebbe partire da 0/valore di partenza del vettore  e finire alla fine del ciclo con 0/valore + lunghezza del vettore considerato in questo tipo ciclo
;loop fatto a partire da un punto nel vettore e finisce in un altro punto specifico
;LOOP1                       
 ;   BEQ FINE
;	leggere da un vettore e fare somma cumulativa
;	LDR R7, [R0], #4 
;	ADD R8, R7, R8
	
;	ADD R4, R4, #1
;	CMP R4, R5
;	B LOOP1
;FINE	

;si entra con indice 0 e si esce all'iterazione Nesima
;LOOP2
	;LDR qualcosa
	;ADD R4, R4, #1
	;CMP R4,R5
	;BNE LOOP2
	
	
	
	
	
	
	
;BUBBLE SORT

;				MOV R2, #0
;				MOV R7, #0
;				LDR R3, =Ordered_quantities
;				LDR R4, =Ordered_Calories
;				SUB R5, R1, #1
				
				
;LOOP1			
;				SUB R6, R5, R2
;				MOV R7, #0
;				MOV R8, R3
;				MOV R9, R4
;				ADD R3, R3, #4
;				ADD R4, R4, #4
;LOOP2
;				
;				LDR R10, [R3]
;				LDR R11, [R3, #8]
;				CMP R10, R11
				
				;è effettivamente minore --- N
				

;				STRLT R11, [R3]
;				STRLT R10, [R3, #8]
;				LDRLT R11, [R3, #-4]
;				LDRLT R10, [R3, #4]
;				STRLT R11, [R3, #4]
;				STRLT R10, [R3, #-4]
;				ADD R3, R3, #8
				
;				LDR R10, [R4]
;				LDR R11, [R4, #8]
;				CMP R10, R11
				
				;è effettivamente minore --- N
				
;				STRLT R11, [R4]
;				STRLT R10, [R4, #8]
;				LDRLT R11, [R4, #-4]
;				LDRLT R10, [R4, #4]
;				STRLT R11, [R4, #4]
;				STRLT R10, [R4, #-4]
;				ADD R4, R4, #8
				
				
				 
				
;				ADD R7, R7, #1
;				CMP R7, R6
;				BNE LOOP2

;ENDLOOP2
;				MOV R3, R8
;				MOV R4,R9
;				ADD R2, R2, #1
;				CMP R2, R5
;				BNE LOOP1
;ENDLOOP1