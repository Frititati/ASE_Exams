
#include "functions.h"
#include "../led/led.h"

// vector size
#define SIZE_N 5

// variables may be needed
volatile int32_t VAR1 = 0;
volatile uint8_t state = 1;
volatile uint8_t blink = 0;
volatile uint8_t waiting_key1 = 0;
volatile uint8_t waiting_key2 = 0;
volatile uint8_t key1_counter = 0;

//vector part
volatile int pointer_vett = 0;
static int32_t VETT[SIZE_N];

extern int count_negative_and_odd(int* VETT, unsigned int n);


void key1_pressed(void) {
	
}

void key2_pressed(void) {
	
}

void int0_pressed(void) {
	
}

void timer0_tick() {
	if (blink == 0) {
		disable_timer(0);
		init_timer(0, 22500000);
		enable_timer(0);
		
		LED_On(0);
		
		blink = 1;
	} else {
		disable_timer(0);
		init_timer(0, 32500000);
		enable_timer(0);
		
		LED_Off(0);
		blink = 0;
	}
}

void timer1_tick() {
	
}

void timer2_tick() {
	
}

void timer3_tick() {
	
}

void joy_up_pressed() {
	if (state == 1) {
		VAR1 = VAR1 + 12;
	}
}

void joy_down_pressed() {
	if (state == 1) {
		VAR1 = VAR1 - 7;
	}
}

void joy_select_pressed() {
	if (state == 1) {
		VETT[pointer_vett] = VAR1;
		pointer_vett++;
		
		VAR1 = 0;
		
		if (pointer_vett == SIZE_N) {
			call_ASM_function();
			pointer_vett = 0;
		}
	}
}


void call_ASM_function(void) {
	uint32_t result;
	result = count_negative_and_odd(VETT, pointer_vett);
	
	disable_timer(0);
	if (result == 0) {
		LED_Out(0);
		init_timer(0, 32500000);
		enable_timer(0);
	} else {
		LED_Off(0);
		LED_Out(result);
	}
	
}

