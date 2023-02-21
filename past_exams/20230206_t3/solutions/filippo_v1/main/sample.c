
#include <stdio.h>
#include "LPC17xx.H"                    /* LPC17xx definitions                */
#include "../led/led.h"
#include "../timer/timer.h"
#include "../button_EXINT/button.h"
#include "../RIT/RIT.h"
#include "../joystick/joystick.h"
#include "../adc/adc.h"
#include "../GLCD/GLCD.h"
#include "../main/functions.h"

#define TIMER0 25000000 //1sec
#define TIMER1 6250000 //0.25sec
#define TIMER2 250000 //0.01sec
#define TIMER3 25000 //0.001sec
#define RITTIMER 0x004C4B40 

#ifdef SIMULATOR
extern uint8_t ScaleFlag; // <- ScaleFlag needs to visible in order for the emulator to find the symbol (can be placed also inside system_LPC17xx.h but since it is RO, it needs more work)
#endif

int main (void) {
	
	SystemInit();  												/* System Initialization (i.e., PLL)  */
	LED_init();                           /* LED Initialization                 */
	BUTTON_init();												/* BUTTON Initialization              */
	joystick_init();
	// ADC_init();
	
	init_RIT(RITTIMER);
	enable_RIT();
	
	init_timer(0, TIMER0);
	init_timer(1, TIMER1);
	init_timer(2, TIMER2);
	init_timer(3, TIMER3);
	//enable_timer(1);
	//enable_timer(2);
	//enable_timer(3);
	//enable_timer(0);
	
	//LCD_Initialization();
	//PESANTE SOLO SE SERVE
	
	//PARTE CHE CI DEVE ESSERE SEMPRE
	LPC_SC->PCON |= 0x1;									/* power-down	mode										*/
	LPC_SC->PCON &= ~(0x2);						
		
	while (1) {                           /* Loop forever                       */	
		__ASM("wfi");
	}

}
