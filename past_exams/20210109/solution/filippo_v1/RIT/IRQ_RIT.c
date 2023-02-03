
#include "lpc17xx.h"
#include "../timer/timer.h"
#include "RIT.h"
#include "../main/functions.h"

extern uint16_t VAR1;

void RIT_IRQHandler (void)
{
	static int J_up = 0;
	static int J_select = 0;
	static int J_down = 0;
	
	// joystick UP
	if((LPC_GPIO1->FIOPIN & (1<<29)) == 0) {
		J_up++;
		switch(J_up){
			case 1: // change to 10
				j_up_press();
				break;
			default:
				break;
		}
	}
	else{
			J_up=0;
	}
	
	// joystick DOWN
	if((LPC_GPIO1->FIOPIN & (1<<26)) == 0) {
		J_down++;
		switch(J_down){
			case 1:
				j_down_press();
				break;
			default:
				break;
		}
	}
	else{
			J_down=0;
	}
	
	// joystick SELECT
	if((LPC_GPIO1->FIOPIN & (1<<25)) == 0) {
		J_select++;
		switch(J_select){
			case 1:
				j_select_press();
				break;
			default:
				break;
		}
	}
	else{
			J_select=0;
	}
	
  LPC_RIT->RICTRL |= 0x1;	/* clear interrupt flag */
	
  return;
}
