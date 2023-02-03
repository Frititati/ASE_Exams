
#include "LPC17xx.h"
#include "led.h"

unsigned char led_value;

void LED_init(void) {
	LPC_PINCON->PINSEL4 &= 0xFFFF0000;
	LPC_GPIO2->FIODIR   |= 0x000000FF;
	LPC_GPIO2->FIOCLR   =  0x000000FF; // all leds off
	// LPC_GPIO2->FIOSET   =  0x000000FF; // all leds on
	
	led_value = 0;
}

void LED_deinit(void) {
	LPC_GPIO2->FIODIR &=   0xFFFFFF00;
}
