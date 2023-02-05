/*********************************************************************************************************
**--------------File Info---------------------------------------------------------------------------------
** File name:           IRQ_timer.c
** Last modified Date:  2014-09-25
** Last Version:        V1.00
** Descriptions:        functions to manage T0 and T1 interrupts
** Correlated files:    timer.h
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
#include "lpc17xx.h"
#include "timer.h"
#include "../led/led.h"

/******************************************************************************
** Function name:		Timer0_IRQHandler
**
** Descriptions:		Timer/Counter 0 interrupt handler
**
** parameters:			None
** Returned value:		None
**
******************************************************************************/
extern unsigned char led_value;					/* defined in funct_led								*/
extern uint8_t stop_acquisition;
extern uint32_t index,average;

void TIMER0_IRQHandler (void)
{	
	/*5.5 second*/
	disable_timer(1);
	disable_timer(0);
	index=0;
	stop_acquisition=0;
	LED_Out(0u);
  LPC_TIM0->IR |= 1;			/* clear interrupt flag */
  return;
}


/******************************************************************************
** Function name:		Timer1_IRQHandler
**
** Descriptions:		Timer/Counter 1 interrupt handler
**
** parameters:			None
** Returned value:		None
**
******************************************************************************/

void TIMER1_IRQHandler (void)
{
	
	/*4hz blink*/
	
	static uint32_t old_res;
	old_res^=average;
	LED_Print_value(old_res);
  LPC_TIM1->IR = 1;			/* clear interrupt flag */
  return;
}


extern char res;


void TIMER2_IRQHandler (void)
{

	
  LPC_TIM2->IR = 1;			/* clear interrupt flag */
  return;
}

/******************************************************************************
**                            End Of File
******************************************************************************/
