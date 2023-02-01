
#include "lpc17xx.h"
#include "../timer/timer.h"
#include "RIT.h"
#include "../main/functions.h"

extern uint16_t VAR1;

void RIT_IRQHandler (void)
{
	static int J_down = 0;
	static int down_KEY2 = 0;
	static int down_INT0 = 0;
	
	// KEY2
	if((LPC_GPIO2->FIOPIN & (1<<12)) == 0) {
		down_KEY2++;
		switch(down_KEY2) {
			case 1:
				key2_press();
				break;
			default:
				break;
		}
	} else{
			down_KEY2=0;
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
	
	// joystick DOWN
	if((LPC_GPIO1->FIOPIN & (1<<26)) == 0) {
		J_down++;
		switch(J_down){
			case 60:
				j_down_press();
				break;
			default:
				break;
		}
	}
	else{
			J_down=0;
	}
	
  LPC_RIT->RICTRL |= 0x1;	/* clear interrupt flag */
	
  return;
}
