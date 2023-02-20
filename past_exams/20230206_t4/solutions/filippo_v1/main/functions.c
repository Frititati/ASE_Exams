
#include "functions.h"
#include "../led/led.h"

// vector size
#define SIZE_N 10

// variables may be needed
volatile unsigned char VAR = 0;
volatile uint8_t state = 0;
volatile uint8_t blink = 0;
volatile uint8_t waiting_key1 = 0;
volatile uint8_t waiting_key2 = 0;
volatile uint8_t key1_counter = 0;

//vector part
volatile int pointer_vett = 0;
static unsigned char VETT[SIZE_N];

char super;
int result;

extern int media_e_superiori_alla_media(unsigned char V[], unsigned int num, char* super);


void key1_pressed(void) {
	int i;
	
	if (state == 0) {
			
		result = media_e_superiori_alla_media(VETT, pointer_vett, &super);
		
		init_timer(0, 6250000);
		enable_timer(0);
		state = 1;
	} else {
		disable_timer(0);
		state = 0;
		for(i = 0; i < SIZE_N; i++) {
			VETT[i] = 0;
		}
		VAR = 0;
		pointer_vett = 0;
		LED_Out(0);
	}
}

void key2_pressed(void) {
	
}

void int0_pressed(void) {
	
}

void timer0_tick() {
	if (blink == 0) {
		LED_Out(result);
		blink = 1;
	} else {
		LED_Out(super);
		blink = 0;
	}
}

void timer1_tick() {
	
}

void timer2_tick() {
	
}

void timer3_tick() {
	if (state == 0) {
		if (pointer_vett < SIZE_N) {
			VETT[pointer_vett] = VAR;
			pointer_vett++;
			VAR = 0;
			LED_Out(0);
		}
	}
}

void joy_up_released(int time) {
	int temp;
	if (state == 0) {
		if (time < 20) {
			VAR += 1;
		} else {
			temp = time / 20;
			VAR += (temp*2);
		}
		LED_Out(VAR);
	}
}


void call_ASM_function(void) {
	
}

