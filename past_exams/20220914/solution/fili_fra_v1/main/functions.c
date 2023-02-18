
#include "functions.h"
#include "../led/led.h"

#define SIZE_N 128

volatile uint32_t pointer_vett = 0;
static int32_t buffer[SIZE_N];

volatile char result;
static uint8_t blink = 0;

extern char DIFF_POS_NEG(int buffer[], unsigned int size, unsigned int *overflow);

void timer2_tick(void) {
	int32_t val_1 = 0;
	int32_t val_3 = 0;
	int32_t result = 0;
	
	disable_timer(1);
	disable_timer(3);
	val_1 = LPC_TIM1->TC;
	val_3 = LPC_TIM3->TC;
	enable_timer(1);
	enable_timer(3);
	
	result = val_3 - val_1;
	LED_Out(result);
	
	buffer[pointer_vett % 128] = result;
	pointer_vett++;
}

void timer0_tick(void) {
	if(blink == 1) {
		LED_Out(0);
		blink = 0;
	} else {
		LED_Out(result);
		blink = 1;
	}
}

void int0_pressed(void) {
	uint32_t overflow;
	disable_timer(1);
	disable_timer(2);
	disable_timer(3);
	
	result = DIFF_POS_NEG(buffer, pointer_vett, &overflow);
	
	if(overflow == 1) {
		init_timer(0, 10000000);
		enable_timer(0);
	} else {
		LED_Out(result);
	}
}

void key1_pressed(void) {
	disable_timer(0);
	enable_timer(1);
	enable_timer(2);
	enable_timer(3);
}

