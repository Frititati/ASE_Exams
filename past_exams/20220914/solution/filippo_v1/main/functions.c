
#include "functions.h"
#include "../led/led.h"

// vector size
#define SIZE_N 128

// variables may be needed
volatile signed int VAR = 0;
volatile uint8_t state = 0;
volatile uint8_t blink = 0;
volatile char result;
volatile uint8_t waiting_key2 = 0;
volatile uint8_t key1_counter = 0;

//vector part
volatile int pointer_vett = 0;
static signed int VETT[SIZE_N];

extern char DIFF_POS_NEG(int buffer[], unsigned int size, unsigned int *overflow);


void key1_pressed(void) {
	if (state == 1) {
		enable_timer(0);
		enable_timer(1);
		enable_timer(3);
		disable_timer(2);
		
		state = 0;		
	}
}

void key2_pressed(void) {
	
}

void int0_pressed(void) {
	uint32_t overflow;
	
	if (state == 0) {
		disable_timer(0);
		disable_timer(1);
		disable_timer(3);
		
		if (pointer_vett < SIZE_N) {
			result = DIFF_POS_NEG(VETT, pointer_vett, &overflow);
		} else {
			result = DIFF_POS_NEG(VETT, SIZE_N, &overflow);
		}
		
		if (overflow != 0) {
			// blink
			init_timer(2, 10000000);
			enable_timer(2);
		} else {
			LED_Out(result);
		}

		state = 1;
	}
}

void timer0_tick() {
	int time1;
	int time3;
	if (state == 0) {
		disable_timer(1);
		disable_timer(3);
		time1 = LPC_TIM1->TC;
		time3 = LPC_TIM3->TC;
		enable_timer(1);
		enable_timer(3);
		
		VAR = time1 - time3;
		
		LED_Out(VAR);
		
		VETT[(pointer_vett % SIZE_N)] = VAR;
		pointer_vett++;
	}
}

void timer1_tick() {
	
}

void timer2_tick() {
	if (blink == 0) {
		LED_Out(0);
		blink = 1;
	} else {
		LED_Out(result);
		blink = 0;
	}
}

void timer3_tick() {
	
}

void joy_up_pressed() {
	
}


void call_ASM_function(void) {
	
}

