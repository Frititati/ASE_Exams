
#include "lpc17xx.h"
#include "timer.h"
#include "../led/led.h"
#include "../GLCD/GLCD.h"
#include "../RIT/RIT.h"
#include "../button_EXINT/button.h"
#include "../adc/adc.h"
#include "../joystick/joystick.h"
#include "../main/functions.h"

// extern unsigned char led_value;					/* defined in funct_led								*/
// extern int RIT_var1;
// static int TIMER0_state1 = 0;
// static int TIMER1_state1 = 0;
// static int TIMER2_state1 = 0;
// static int TIMER3_state1 = 0;

void TIMER0_IRQHandler (void)
{
	// int i=0;
	NVIC_DisableIRQ(TIMER0_IRQn);

	// timer0_tick();
	
	/*if(TIMER0_state1==x) state può essere binario oppure un valore ricavato da un calcolo per tot ripetizioni a tot frequenza
	{
		...
	}
	else
	{
	TIMER0_state1 = 0;
	}*/
	
	NVIC_EnableIRQ(TIMER0_IRQn);
	LPC_TIM0->IR |= 1;			/* clear interrupt flag */
	return;
}


void TIMER1_IRQHandler (void)
{
	// int i=0;
	NVIC_DisableIRQ(TIMER1_IRQn);
	
	timer1_tick();
	
	
	/*if(TIMER1_state1==x) state può essere binario oppure un valore ricavato da un calcolo per tot ripetizioni a tot frequenza
	{
		...
	}
	else
	{
	TIMER1_state1 = 0;
	}*/
	
	
	
	NVIC_EnableIRQ(TIMER1_IRQn);
	LPC_TIM1->IR = 1;			/* clear interrupt flag */
	return;
}

void TIMER2_IRQHandler (void)
{
	// int i=0;
	NVIC_DisableIRQ(TIMER2_IRQn);

	timer2_tick();
	
	/*if(TIMER2_state1==x) state può essere binario oppure un valore ricavato da un calcolo per tot ripetizioni a tot frequenza
	{
		...
	}
	else
	{
	TIMER2_state2 = 0;
	}*/
	
	NVIC_EnableIRQ(TIMER2_IRQn);
	LPC_TIM2->IR = 1;			/* clear interrupt flag */
	return;
}

void TIMER3_IRQHandler (void)
{
	// int i=0;
	NVIC_DisableIRQ(TIMER3_IRQn);

	// timer3_tick();
	
	/*if(TIMER3_state1==x) state può essere binario oppure un valore ricavato da un calcolo per tot ripetizioni a tot frequenza
	{
		...
	}
	else
	{
	TIMER4_state2 = 0;
	}*/
	
	NVIC_EnableIRQ(TIMER3_IRQn);
	LPC_TIM3->IR = 1;			/* clear interrupt flag */
	return;
}

