
#include "functions.h"
#include "../led/led.h"

#define SIZE_N 10

static unsigned char VAL = 0;
static int pointer_vett = 0;
static unsigned char VETT[SIZE_N];

static uint8_t key1_counter = 0;

static uint8_t blink = 0;

extern unsigned char get_and_sort(unsigned char* VETT, unsigned char VAL, int n);

void key1_pressed(void) {
	uint32_t time;
	disable_timer(1);
	time = LPC_TIM1->TC;
	enable_timer(1);
	
	VAL = time >> 16;
	
	get_and_sort(VETT, VAL, pointer_vett);
	
	pointer_vett++;
	LED_Out(pointer_vett);
	
	if(pointer_vett == SIZE_N) {
		// start LED procedure
		init_timer(0, 50000000);
		enable_timer(0);
	}
}

void timer0_tick(void) {
	LED_Out(VETT[blink]);
	blink++;
	
	if (blink == SIZE_N) {
		LED_Out(0);
		blink = 0;
		pointer_vett = 0;
		disable_timer(0);
	}
}

void key2_pressed(void) {
	
}

