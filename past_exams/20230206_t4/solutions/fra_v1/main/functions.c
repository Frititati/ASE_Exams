
#include "functions.h"
#include "../led/led.h"

// vector size
#define N 4

// variables may be needed
volatile uint8_t VAR = 0;
volatile uint8_t state = 0;
volatile uint8_t blink = 0;
volatile uint8_t waiting_key1 = 0;
volatile uint8_t waiting_key2 = 0;
volatile uint8_t key1_counter = 0;

//vector part
volatile int pointer_vett = 0;
static unsigned char  VETT[N];
volatile int time = 0;
volatile int result;

char super;
extern int media_e_superiori_alla_media(unsigned char *VETT, unsigned int n, char* super);

volatile int time;
static int i;
static int n_times;

void key1_pressed(void) {
	if (state == 0){
		result = media_e_superiori_alla_media(VETT, N, &super);
		LED_Out(result);
		enable_timer(1);
		blink = 0;
		state = 1;
	} else{
		reset_timer(1);
		reset_timer(3);
		disable_timer(1);
		for (i = 1; i < N; i++){
			VETT[i] = 0;
		}
		pointer_vett = 0;
		LED_Out(0);
		state = 0;
	}
}

void key2_pressed(void) {
	
}

void int0_pressed(void) {
	
}

void timer0_tick() {
	
}

void timer1_tick() {
	if (blink == 0){
		LED_Out(super);
		blink = 1;
	} else{
		LED_Out(result);
		blink = 0;
	}
}

void timer2_tick() {
	
}

void timer3_tick() {
	if (pointer_vett < N){
		VETT[pointer_vett] = VAR;
		pointer_vett++;
		LED_Out(0);
	}	
}

void joy_up_released() {
	if (time < 20){
		VAR++;
	} else {
		n_times = time / 20;
		VAR += ((n_times) * 2);
	}
	LED_Out(VAR);
}


void call_ASM_function(void) {
	
}

