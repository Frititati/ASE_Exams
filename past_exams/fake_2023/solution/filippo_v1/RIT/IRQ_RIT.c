
#include "lpc17xx.h"
#include "../timer/timer.h"
#include "RIT.h"
#include "../main/functions.h"

void RIT_IRQHandler (void)
{
	static int pressedKEY2 = 0;
	static int pressedKEY1 = 0;
	static int pressedINT0 = 0;
	
	if((LPC_PINCON->PINSEL4 & (1 << 24)) == 0){
		pressedKEY2++;
		if((LPC_GPIO2->FIOPIN & (1<<12)) == 0){   //key2
			reset_RIT();
			switch(pressedKEY2){
				case 1:
					key2_pressed();
					break;
				default:
					break;
			}
		}
		else {	/* button released */
			pressedKEY2=0;
			disable_RIT();
			reset_RIT();
			NVIC_EnableIRQ(EINT2_IRQn);							 /* disable Button interrupts			*/
			LPC_PINCON->PINSEL4    |= (1 << 24);     /* External interrupt 0 pin selection */
		}
	}
	
	
	if((LPC_PINCON->PINSEL4 & (1 << 22)) == 0){
		pressedKEY1++;
		if((LPC_GPIO2->FIOPIN & (1<<11)) == 0){   //key1
			reset_RIT(); // si può rimuovere
			switch(pressedKEY1){
				case 1:
					key1_pressed();
					break;
				default:
					break;
			}
		}
		else {	/* button released */
			pressedKEY1=0;
			disable_RIT();
			reset_RIT();
			NVIC_EnableIRQ(EINT1_IRQn);							 /* disable Button interrupts			*/
			LPC_PINCON->PINSEL4    |= (1 << 22);     /* External interrupt 0 pin selection */
		}
	}
	
	
	if((LPC_PINCON->PINSEL4 & (1 << 20)) == 0){
		pressedINT0++;
		if((LPC_GPIO2->FIOPIN & (1<<10)) == 0){   //int0
			reset_RIT();
			switch(pressedINT0){
				case 1:
					int0_pressed();
					break;
				default:
					break;
			}
		}
		else {	/* button released */
			pressedINT0=0;
			disable_RIT();
			reset_RIT();
			NVIC_EnableIRQ(EINT0_IRQn);							 /* disable Button interrupts			*/
			LPC_PINCON->PINSEL4    |= (1 << 20);     /* External interrupt 0 pin selection */
		}
	}	
	
	
  LPC_RIT->RICTRL |= 0x1;	/* clear interrupt flag */
	
  return;
}
