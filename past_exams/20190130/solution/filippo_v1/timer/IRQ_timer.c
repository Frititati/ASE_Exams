
#include "LPC17XX.h"
#include "timer.h"
#include "../GLCD/functions.h"
#include "../music/music_play.h"

extern uint8_t menu_selection;

volatile uint8_t happiness_counter = 0;
volatile uint8_t satiety_counter = 0;
extern unsigned short volume;

void TIMER0_IRQHandler (void)
{
	timer_tick();
	
  LPC_TIM0->IR = 1;			/* clear interrupt flag */
  return;
}

void TIMER1_IRQHandler (void)
{
	static int sineticks=0;
	/* DAC management */
	static int currentValue;
	currentValue = SinTable[sineticks]/4 * volume;
	LPC_DAC->DACR = (currentValue <<6);
	sineticks++;
	if(sineticks==45) sineticks=0;
	
  LPC_TIM1->IR = 1;			/* clear interrupt flag */
  return;
}

void TIMER2_IRQHandler (void)
{
	disable_timer(1);
	timer2Interrupt();
  LPC_TIM2->IR = 1;			/* clear interrupt flag */
  return;
}
