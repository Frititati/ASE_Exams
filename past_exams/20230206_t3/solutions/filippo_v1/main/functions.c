
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

volatile int result;
static char overflow;

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
		disable_timer(2);
		disable_timer(0);
		
		state = 1;
		
		if (pointer_vett > SIZE_N) {
			result = differenza_media_positivi_negativi(VETT, SIZE_N, &overflow);
		} else {
			result = differenza_media_positivi_negativi(VETT, pointer_vett, &overflow);
		}
		
		if (overflow == 0xFF) {
			// has overflow
			init_timer(1, 4166666); // 3HZ
			enable_timer(1);
		} else {
			// no overflow
			if (result >= 0) {
				LED_Out(255);
			} else {
				LED_Out(0);
				LED_On(7);
			}
		}
		
	} else {
		disable_timer(0);
		enable_timer(2);
		LED_Out(0);
		
		pointer_vett = 0;
		state = 0;
		
		for (i = 0; i < SIZE_N; i++) {
			VETT[i] = 0;
		}
	}
}

void timer0_tick() {
	if (blink == 0) {
		LED_Out(0);
		blink = 1;
	} else {
		LED_Out(3);
		blink = 0;
	}
}

void timer1_tick() {
	if (blink == 0) {
		LED_Out(0);
		blink = 1;
	} else {
		LED_Out(255);
		blink = 0;
	}
}

void timer2_tick() {
	
}

void timer3_tick() {
	
}

void joy_down_pressed() {
	int time;
	int temp;
	if (state == 0) {
		disable_timer(2);
		time = LPC_TIM2->TC;
		enable_timer(2);
		
		VETT[(pointer_vett % SIZE_N)] = time;
		pointer_vett++;
		
		temp = (pointer_vett / SIZE_N) - 1;
		
		if (temp == -1) {
			LED_Out(0);
		} else if(temp > 4) {
			// blink
			init_timer(0, 6250000);
			enable_timer(0);
		} else {
			LED_Out(temp - 1);
		}
		
	}
}


void call_ASM_function(void) {
	
}

