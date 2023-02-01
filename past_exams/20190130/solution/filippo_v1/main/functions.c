
#include "functions.h"
#include "../led/led.h"

volatile uint32_t VAR1 = 0;
volatile int result = 0;
extern int count_bits_to_1(unsigned);

void reset(void) {
	VAR1 = 9;
}

void key2_press(void) {
	disable_timer(3);
	VAR1 += LPC_TIM3->TC;
	enable_timer(3);
}

void int0_press(void) {
	VAR1 = VAR1 >> 2;
}

void j_down_press(void) {
	
	// stop the timer in case of previous round
	led_timer_stop();
	
	// call assembly
	result = count_bits_to_1(VAR1);
	
	if (result < 4) {
		LED_Out(0);
	}
	if (result > 3 && result < 12) {
		LED_On(result - 4);
	}
	if (result > 11 && result < 32) {
		led_timer_start();
	}
	
	reset();
}

void led_timer_start(void) {
	init_timer(0, 15000000);
	enable_timer(0);
}

void led_timer_stop(void) {
	disable_timer(0);
	LPC_GPIO2->FIOCLR   =  0x000000FF;
}

void led_timer_tick(void) {
	static int tick = 0;
	
	if ((tick % 2) == 0) {
		LPC_GPIO2->FIOSET   =  0x000000FF;
	} else {
		LPC_GPIO2->FIOCLR   =  0x000000FF;
	}
	tick++;
}
