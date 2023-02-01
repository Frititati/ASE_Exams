/****************************************Copyright (c)****************************************************
**                                      
**                                 http://www.powermcu.com
**
**--------------File Info---------------------------------------------------------------------------------
** File name:               main.c
** Descriptions:            The GLCD application function
**
**--------------------------------------------------------------------------------------------------------
** Created by:              AVRman
** Created date:            2010-11-7
** Version:                 v1.0
** Descriptions:            The original version
**
**--------------------------------------------------------------------------------------------------------
** Modified by:             Paolo Bernardi
** Modified date:           03/01/2020
** Version:                 v2.0
** Descriptions:            basic program for LCD and Touch Panel teaching
**
*********************************************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "LPC17xx.h"
#include "GLCD/functions.h"
#include "TouchPanel/TouchPanel.h"
#include "timer/timer.h"
#include "RIT/RIT.h"
#include "joystick/joystick.h"
#include "adc/adc.h"

#define SIMULATOR 1

#ifdef SIMULATOR
extern uint8_t ScaleFlag; // <- ScaleFlag needs to visible in order for the emulator to find the symbol (can be placed also inside system_LPC17xx.h but since it is RO, it needs more work)
#endif

volatile uint8_t hr = 0;
volatile uint8_t min = 0;
volatile uint8_t sec = 0;
volatile uint8_t menu_selection = 0;

volatile uint8_t happiness = 0;
volatile uint8_t satiety = 0;
volatile uint8_t state = 9;
volatile uint8_t joystick_flag = 0;

volatile unsigned short volume = 0;

int main(void)
{
  SystemInit();  												/* System Initialization (i.e., PLL)  */
	joystick_init();
	init_LCD();
	ADC_init();
	TP_Init();
	TouchPanel_Calibrate();
	
	init_timer(0, 0x017D7840); 	            /* 1s * 25MHz = 25000000 ~= 0x017D7840 */
	init_RIT(0x004C4B40);										/* RIT inizialization to 50 ms = 0x004C4B40*/
	
	// only first time
	timer_tick();
	
	enable_timer(0);
	enable_RIT();
	
	LPC_SC->PCON |= 0x1;									/* power-down	mode										*/
	LPC_SC->PCON &= ~(0x2);

	LPC_PINCON->PINSEL1 |= (1<<21);
	LPC_PINCON->PINSEL1 &= ~(1<<20);
	LPC_GPIO0->FIODIR |= (1<<26);					
	
  while (1)	
  {
//		__ASM("wfi");
  }
}

/*********************************************************************************************************
      END FILE
*********************************************************************************************************/
