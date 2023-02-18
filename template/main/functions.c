
#include "functions.h"
#include "../led/led.h"

#define SIZE_N 5

// set to volatile such that the watch window can work correctly
static unsigned char VAR = 0;
static int pointer_vett = 0;
static unsigned char VETT[SIZE_N];

static uint8_t waiting_key1 = 1;
static uint8_t waiting_key2 = 0;

static uint8_t key1_counter = 0;

static uint8_t blink = 0;

extern unsigned int monotono_crescente(unsigned char *VETT, unsigned int n);

void reset(void) {
	VAR = 0;
}

void timer1_tick() {
	VAR++;
}

void timer2_tick() {
	LED_Out(pointer_vett);
	if (blink == 0) {
		if(waiting_key1 == 1) {
			LED_On(7);
		} else {
			LED_Off(7);
		}
		
		if(waiting_key2 == 1) {
			LED_On(6);
		} else {
			LED_Off(6);
		}
		blink = 1;
	} else {
		LED_Off(7);
		LED_Off(6);
		blink = 0;
	}
}

void key1_pressed(void) {
	if (waiting_key1 == 1) {
		key1_counter++;
		if(key1_counter == 2) {
			waiting_key1 = 0;
			waiting_key2 = 0;
			// call ASM
			
			call_ASM_function();
		
		} else {
			waiting_key2 = 1;
		}
	}
}

void key2_pressed(void) {
	if (waiting_key2 == 1) {
		disable_timer(1);
		VETT[pointer_vett] = VAR;
		enable_timer(1);
		
		pointer_vett++;

		waiting_key1 = 1;
		waiting_key2 = 0;
		key1_counter = 0;
		
		if(pointer_vett == SIZE_N) {
			// call ASM
			call_ASM_function();
			LED_On(0);
		}
	}
}

void call_ASM_function(void) {
	int result = 0;
	
	disable_timer(1);
	disable_timer(2);
	
	result = monotono_crescente(VETT, pointer_vett);
	LED_Out(result);
	
	waiting_key1 = 0;
	waiting_key2 = 0;
	key1_counter = 0;
}

void int0_pressed(void) {
	waiting_key1 = 1;
	waiting_key2 = 0;
	key1_counter = 0;
	enable_timer(1);
	enable_timer(2);
	pointer_vett = 0;
}

