
#include "functions.h"
#include "../led/led.h"

volatile uint8_t e1 = 0;
volatile uint8_t e2 = 0;

volatile uint8_t state = 0;

extern int divisible(int e1, int e2);


void int0_pressed(void) {
	disable_timer(2);
	reset_timer(2);
	init_timer(2, 163525000);
	enable_timer(2);
	state = 1;
}

void key1_pressed(void) {
	if (state == 1) {
		e1++;
		LED_Out_e(e1);
	}
}

void key2_pressed(void) {
	if (state == 1) {
		e2++;
	}
}
void timer2_tick() {
	uint8_t result;
	if (state == 1) {
		state = 0;
		// call ASM
		result = divisible(e1, e2);
		
		LED_Out_res(result);
		
		state = 0;
		e1 = 0;
		e2 = 0;
	}
}

