
#include "LPC17XX.h"
#include "timer.h"
#include "../main/functions.h"

void TIMER0_IRQHandler (void)
{
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

void TIMER3_IRQHandler (void)
{
	timer3_tick();
  LPC_TIM3->IR = 1;			/* clear interrupt flag */
  return;
}
