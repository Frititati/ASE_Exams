/*********************************************************************************************************
**--------------File Info---------------------------------------------------------------------------------
** File name:           IRQ_RIT.c
** Last modified Date:  2014-09-25
** Last Version:        V1.00
** Descriptions:        functions to manage T0 and T1 interrupts
** Correlated files:    RIT.h
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
#include "lpc17xx.h"
#include "RIT.h"
#include "../led/led.h"
#include "../timer/timer.h"

/******************************************************************************
** Function name:		RIT_IRQHandler
**
** Descriptions:		REPETITIVE INTERRUPT TIMER handler
**
** parameters:			None
** Returned value:		None
**
******************************************************************************/

#define N 50

uint32_t var;
uint32_t vett[N];

uint8_t stop_acquisition;
uint32_t index,average;

extern unsigned int media_pressioni_con_filtro(unsigned int VETT[], 
                            unsigned int numero_misure, unsigned int REMOVE);


void RIT_IRQHandler (void)
{			
	static int down=0;	
	static int down0=0;
	static uint8_t position=0;
	float value;
	const unsigned int remove =5;
	int val_int;
	if((LPC_PINCON->PINSEL4 & (1 << 22)) == 0){
		if((LPC_GPIO2->FIOPIN & (1<<11)) == 0){   //key1
			reset_RIT(); 
					down++;
		}
		else {	/* button released */
			if(	!stop_acquisition){
			value=(float)(down*0.05); /*ms*/
			val_int=(uint32_t) value; /*brutally cast, it cuts off the mantissa*/
			var= val_int>8 ? 0 : val_int;
			LED_Print_value(var);
			}
			down=0;			
			disable_RIT();
			reset_RIT();
			NVIC_EnableIRQ(EINT1_IRQn);							 /* disable Button interrupts			*/
			LPC_PINCON->PINSEL4    |= (1 << 22);     /* External interrupt 0 pin selection */
		}
	}			
	
	/*int0*/
	if((LPC_PINCON->PINSEL4 & (1 << 20)) == 0){
		down0++;
		if((LPC_GPIO2->FIOPIN & (1<<10)) == 0){   //int0
			reset_RIT();
			switch(down0){
				case 1:
					
				if(index==N){
					media_pressioni_con_filtro(vett,index,remove);
					stop_acquisition=1;
					LED_Print_value(average);
					enable_timer(1);
					enable_timer(0); // for 5.5 sec
				}else {
				
					vett[index++]=var;
				}
					break;
				default:
					break;
			}
		}
		else {	/* button released */
			down0=0;			
			disable_RIT();
			reset_RIT();
			NVIC_EnableIRQ(EINT0_IRQn);							 /* disable Button interrupts			*/
			LPC_PINCON->PINSEL4    |= (1 << 20);     /* External interrupt 0 pin selection */
		}
	}	
	
  LPC_RIT->RICTRL |= 0x1;	/* clear interrupt flag */
	
  return;
}

/******************************************************************************
**                            End Of File
******************************************************************************/
