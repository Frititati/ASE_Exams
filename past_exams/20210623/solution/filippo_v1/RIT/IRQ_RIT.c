
#include "lpc17xx.h"
#include "../timer/timer.h"
#include "RIT.h"
#include "../main/functions.h"

extern uint16_t VAR1;

void RIT_IRQHandler (void)
{
	static int J_up = 0;
	static int J_left = 0;
	static int J_select = 0;
	static int down_INT0 = 0;
	
	// joystick UP
	if((LPC_GPIO1->FIOPIN & (1<<29)) == 0) {
		J_up++;
		switch(J_up){
			case 2: // change to 10
				j_up_press();
				J_up = 0;
				break;
			default:
				break;
		}
	}
	else{
			J_up=0;
	}
	
	// joystick LEFT
	if((LPC_GPIO1->FIOPIN & (1<<27)) == 0) {
		J_left++;
		switch(J_left){
			case 2: // change to 10
				j_left_press();
				J_left = 0;
				break;
			default:
				break;
		}
	}
	else{
			J_left=0;
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
	
	// INT0
	if((LPC_GPIO2->FIOPIN & (1<<10)) == 0) {
		down_INT0++;
		switch(down_INT0) {
			case 1:
				int0_press();
				break;
			default:
				break;
		}
	} else{
			down_INT0=0;
	}
	
  LPC_RIT->RICTRL |= 0x1;	/* clear interrupt flag */
	
  return;
}
