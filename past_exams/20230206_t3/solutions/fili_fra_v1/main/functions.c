
#include "functions.h"
#include "../led/led.h"

// vector size
#define SIZE_N 4

// variables may be needed
volatile unsigned char VAR = 0;
volatile uint8_t state = 0;
volatile uint8_t blink = 0;
volatile uint8_t waiting_key1 = 0;
volatile uint8_t waiting_key2 = 0;
volatile uint8_t key1_counter = 0;

//vector part
volatile int pointer_vett = 0;
static int VETT[SIZE_N];

extern int differenza_media_positivi_negativi(int V[], unsigned int num, char* over);


void key1_pressed(void) {
	
}

void key2_pressed(void) {
	
}

void int0_pressed(void) {
	int i;
	if (state == 0) {
		state = 1;
		call_ASM_function();
	} else {
		// state 1
		disable_timer(1);
		disable_timer(3);
		
		pointer_vett = 0;
		for (i = 0; i < SIZE_N; i++) {
			VETT[i] = 0;
		}
		state = 0;
		
		LED_Out(0);
	}
		
}

void timer0_tick() {
	
}

void timer1_tick() {
	if (blink == 0) {
		LED_On(6);
		LED_On(7);
		blink = 1;
	} else {
		LED_Off(6);
		LED_Off(7);
		blink = 0;
	}
}

void timer2_tick() {
	
}

void timer3_tick() {
	if (blink == 0) {
		LED_Out(0);
		blink = 1;
	} else {
		LED_Out(255);
		blink = 0;
	}
}

void joy_down_pressed() {
	int time;
	uint8_t times_full;
	
	if (state == 0) {
		disable_timer(2);
		time = LPC_TIM2->TC;
		enable_timer(2);
		VETT[(pointer_vett % SIZE_N)] = time;
		pointer_vett++;
	
		times_full = pointer_vett / SIZE_N;
		if (times_full < 4) {
			LED_Last(times_full);
		} else {
			// enable blinking timer
			init_timer(1, 6250000);
			enable_timer(1);
		}
	}
}


void call_ASM_function(void) {
	char overflow;
	int result;
	
	disable_timer(1);
	
	if (pointer_vett > SIZE_N) {
		result = differenza_media_positivi_negativi(VETT, SIZE_N, &overflow);
	} else {
		result = differenza_media_positivi_negativi(VETT, pointer_vett, &overflow);
	}
	
	if (overflow == 0) {
		if (result > 0) {
			LED_Out(255);
		} else {
			LED_Out(0);
			LED_On(0);
		}
	} else {
		init_timer(3, 4162500);
		enable_timer(3);
	}	
}

