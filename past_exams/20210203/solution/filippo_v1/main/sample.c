
#include "LPC17xx.h"
#include "../timer/timer.h"
#include "../RIT/RIT.h"
#include "../joystick/joystick.h"
#include "../led/led.h"
#include "functions.h"

#define SIMULATOR 1

#ifdef SIMULATOR
extern uint8_t ScaleFlag; // <- ScaleFlag needs to visible in order for the emulator to find the symbol (can be placed also inside system_LPC17xx.h but since it is RO, it needs more work)
#endif

int main(void)
{
  SystemInit();  												/* System Initialization (i.e., PLL)  */
	
	joystick_init();
	LED_init();

	init_RIT(0x002625A0);										/* RIT inizialization to 50 ms = 0x004C4B40*/
	
	enable_timer(3);
	enable_RIT();
	
	reset();
	
	LPC_SC->PCON |= 0x1;									/* power-down	mode										*/
	LPC_SC->PCON &= ~(0x2);					
	
  while (1)	
  {
		__ASM("wfi");
  }
}
