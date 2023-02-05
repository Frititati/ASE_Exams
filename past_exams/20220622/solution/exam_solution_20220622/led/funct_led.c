/*********************************************************************************************************
**--------------File Info---------------------------------------------------------------------------------
** File name:           funct_led.h
** Last modified Date:  2014-09-25
** Last Version:        V1.00
** Descriptions:        High level led management functions
** Correlated files:    lib_led.c, funct_led.c
**--------------------------------------------------------------------------------------------------------       
*********************************************************************************************************/

#include "lpc17xx.h"
#include "led.h"

#define LED_NUM     8                   /* Number of user LEDs                */
const unsigned long led_mask[] = { 1UL<<0, 1UL<<1, 1UL<<2, 1UL<< 3, 1UL<< 4, 1UL<< 5, 1UL<< 6, 1UL<< 7 };

extern unsigned char led_value;

/*----------------------------------------------------------------------------
  Function that turns on requested LED
 *----------------------------------------------------------------------------*/
void LED_On(unsigned int num) {
 
  LPC_GPIO2->FIOPIN |= led_mask[num];
	//led_value = LPC_GPIO2->FIOPIN;
}

/*----------------------------------------------------------------------------
  Function that turns off requested LED
 *----------------------------------------------------------------------------*/
void LED_Off(unsigned int num) {

  LPC_GPIO2->FIOPIN &= ~led_mask[num];
	//led_value = LPC_GPIO2->FIOPIN;
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
//	led_value = value;
}

#define LED_EVEN_MASK 0x55
/*p2.0 -> 11*/
/*p2.1 -> 10*/
/*p2.2 -> 9*/
/*p2.3 -> 8*/
/*p2.4 -> 7*/
/*p2.5 -> 6*/
/*p2.6 -> 5*/
/*p2.7 -> 4*/

const uint8_t converter [] = {
	/*1 sec*/1,
	/*2sec*/16, /*0x10*/
	/*3sec*/ 0x40,
	/*4sec*/ 0x80,
	/*5sec*/ 0x02,
	/*6sec*/ 0x04,
	/*7sec*/ 0x20,
	/*8sec*/ 0x80,
};

void LED_Print_value(uint32_t value){

	if(value>=1 &&  value<=8){
	LED_Out((converter[value-1])&0x000000ff);
	}else {
	/*==0*/
	LED_Out(LED_EVEN_MASK);
	}

}