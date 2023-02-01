
#include "lpc17xx.h"
#include "../timer/timer.h"
#include "RIT.h"
#include "../music/music_play.h"
#include "../TouchPanel/TouchPanel.h"
#include "../ADC/adc.h"
#include "../GLCD/functions.h"

#define RIT_SEMIMINIMA 8
#define RIT_MINIMA 16
#define RIT_INTERA 32

#define UPTICKS 1

extern uint8_t menu_selection;
extern uint8_t state;
extern uint8_t joystick_flag;

void RIT_IRQHandler (void)
{			
	static int select=0;
	static int J_right = 0;
	static int J_left = 0;
	
	ADC_start_conversion();
	getDisplayPoint(&display, Read_Ads7846(), &matrix);
	evalutateTouchScreen(&display);
	
	if((LPC_GPIO1->FIOPIN & (1<<28)) == 0) {	
		/* Joytick Right pressed p1.26 --> using J_DOWN due to emulator issues*/
		
		J_right++;
		switch(J_right){
			case 1:
				menu_selection = 1;
				break;
			default:
				break;
		}
	}
	else{
			J_right=0;
	}
	
	if((LPC_GPIO1->FIOPIN & (1<<27)) == 0) {	
		/* Joytick Left pressed p1.26 --> using J_DOWN due to emulator issues*/
		
		J_left++;
		switch(J_left){
			case 1:
				menu_selection = 0;
				break;
			default:
				break;
		}
	}
	else{
			J_left=0;
	}
	
	if((LPC_GPIO1->FIOPIN & (1<<25)) == 0){	
		/* Joytick Select pressed p1.25 --> NOT WORKING WITH EMULATOR*/
		select++;
		switch(select){
			case 1:
				if (state == 6){
					enable_timer(0);
					state = 9;
				}
				
				if (state == 0) {
					if(menu_selection == 0){
						// spaw food
						joystick_flag = 1;
						play(PlayTypeClick);
					}
					if(menu_selection == 1){
						// spaw food
						joystick_flag = 2;
						play(PlayTypeClick);
					}
				}
				break;
			default:
				break;
		}
	} else {
		select=0;
	}
	
  LPC_RIT->RICTRL |= 0x1;	/* clear interrupt flag */
	
  return;
}

/******************************************************************************
**                            End Of File
******************************************************************************/
