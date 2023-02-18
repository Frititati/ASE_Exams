#include "button.h"
#include "lpc17xx.h"

#include "../led/led.h" 					/* do not needed anymore, make your project clean */
#include "../RIT/RIT.h"		  			/* you now need RIT library 			 */
//#include "../timer/timer.h"
//#include "../GLCD/GLCD.h"
//#include "../adc/adc.h"
//#include "../joystick/joystick.h"


/*USARE SE SI VUOLE TENERE IL RIT ACCESO ANCHE COL DEBOUNCING, UTILE SE SI VUOLE
  IN CUI SUCCEDE QUALCOSA A LIVELLO PERIODICO E NON SI VUOLE IMPLEMENTARE UN TIMER
	PER FARLO MA FARLO DIRETTAMENTE NEL RIT, TIPO MULTIPLI DI 50 MS
*/
uint8_t stateINT0=0;
uint8_t stateKEY1=0;
uint8_t stateKEY2=0;

void EINT0_IRQHandler (void)	  	/* INT0														 */
{	
	stateINT0=1;	
	enable_RIT();										/* enable RIT to count 50ms				 */
	NVIC_DisableIRQ(EINT0_IRQn);		/* disable Button interrupts			 */
	LPC_PINCON->PINSEL4    &= ~(1 << 20);     /* GPIO pin selection */
	
	//NON USARE QUESTO -> RIT DEBOUNCING
	
	LPC_SC->EXTINT &= (1 << 0);     /* clear pending interrupt         */
}


void EINT1_IRQHandler (void)	  	/* KEY1														 */
{
	stateKEY1=1;
	enable_RIT();										/* enable RIT to count 50ms				 */
	NVIC_DisableIRQ(EINT1_IRQn);		/* disable Button interrupts			 */
	LPC_PINCON->PINSEL4    &= ~(1 << 22);     /* GPIO pin selection */
	
	//NON USARE QUESTO -> RIT DEBOUNCING
	
	LPC_SC->EXTINT &= (1 << 1);     /* clear pending interrupt         */
}

void EINT2_IRQHandler (void)	  	/* KEY2														 */
{
	stateKEY2=1;
	enable_RIT();
	NVIC_DisableIRQ(EINT2_IRQn);  
	//NON USARE QUESTO -> RIT DEBOUNCING
	
	LPC_PINCON->PINSEL4 &= ~(1<<24);
  LPC_SC->EXTINT &= (1 << 2);     /* clear pending interrupt         */    
}


