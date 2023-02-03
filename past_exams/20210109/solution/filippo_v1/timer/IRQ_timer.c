
#include "LPC17XX.h"
#include "timer.h"
#include "../main/functions.h"

void TIMER0_IRQHandler (void)
{
	timer0_tick();
  LPC_TIM0->IR = 1;			/* clear interrupt flag */
  return;
}

void TIMER1_IRQHandler (void)
{	
  LPC_TIM1->IR = 1;			/* clear interrupt flag */
  return;
}

void TIMER2_IRQHandler (void)
{
  LPC_TIM2->IR = 1;			/* clear interrupt flag */
  return;
}
