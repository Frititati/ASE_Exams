
#include "functions.h"
#include "../led/led.h"

#define SIZE_N 5

// set to volatile such that the watch window can work correctly
volatile int32_t VAR1 = 0;

static int display_lock = 0;
static int32_t VETT[SIZE_N];
static int pointer_vett = 0;

static int led_counter = 0;

extern unsigned int count_negative_and_odd(int32_t *VETT, unsigned int n);

void reset(void) {
	VAR1 = 0;
}

void j_up_press(void) {
	if (display_lock == 0) {
		VAR1 = VAR1 + 12;
	}
}

void j_down_press(void) {
	if (display_lock == 0) {
		VAR1 = VAR1 - 7;
	}
}

void j_select_press(void) {
	// value ready
	if (display_lock == 0) {
		VETT[pointer_vett] = VAR1;
		pointer_vett++;
		VAR1 = 0;
		if (pointer_vett == SIZE_N) {
			call_count();
		}
	} else {
		// executed only when lock is present
		display_lock = 0;
		disable_timer(0);
		LED_Off(0);
	}
}

void call_count(void) {
	int result;
	result = count_negative_and_odd(VETT, pointer_vett);
	
	if(result != 0) {
		LED_Out(result);
	} else {
		timer0_tick();
	}
	display_lock = 1;
	pointer_vett = 0;
	VAR1 = 0;
}

void timer0_tick(void) {
	if (led_counter == 1) {
		disable_timer(0);
		
		LED_On(0);
		led_counter = 0;
		
		init_timer(0, 32500000); // 1.3 second timer
		enable_timer(0);
	} else {
		disable_timer(0);
		
		LED_Off(0);
		
		led_counter = 1;
		
		init_timer(0, 22500000);
		enable_timer(0);
	}
}

