
#include "lpc17xx.h"
#include "led.h"
//#include "../button_EXINT/button.h"
//#include "../RIT/RIT.h"
//#include "../timer/timer.h"
//#include "../GLCD/GLCD.h"
//#include "../adc/adc.h"
//#include "../joystick/joystick.h"

#define LED_NUM     8                   /* Number of user LEDs                */

//const unsigned long led_mask[] = { 1UL<<0, 1UL<<1, 1UL<<2, 1UL<<3, 1UL<<4, 1UL<<5, 1UL<<6, 1UL<<7};
const unsigned long led_mask[] = { 1UL<<7, 1UL<<6, 1UL<<5, 1UL<<4, 1UL<<3, 1UL<<2, 1UL<<1, 1UL<<0};

extern unsigned char led_value;

/*----------------------------------------------------------------------------
  Function that turns on requested LED
 *----------------------------------------------------------------------------*/
void LED_On(unsigned int num) {
 
  LPC_GPIO2->FIOPIN |= led_mask[num];
	led_value = LPC_GPIO2->FIOPIN;
}

/*----------------------------------------------------------------------------
  Function that turns off requested LED
 *----------------------------------------------------------------------------*/
void LED_Off(unsigned int num) {

  LPC_GPIO2->FIOPIN &= ~led_mask[num];
	led_value = LPC_GPIO2->FIOPIN;
}

/*----------------------------------------------------------------------------
  Function that outputs value to LEDs
 *----------------------------------------------------------------------------*/
void LED_Out(unsigned int value) {
  int i;

  for (i = 0; i < LED_NUM; i++) {
    if (value & (1<<i)) {
      LED_On (i);
    } else {
      LED_Off(i);
    }
  }
	led_value = value;
}

// if needed we can split the value of i to control only part of the led in LED_OUT

void LED_single_one(unsigned int value)
{
	int i;
	for(i=0; i<LED_NUM;i++) LED_Off (i);
	LED_On(value);
	led_value=value;
}
