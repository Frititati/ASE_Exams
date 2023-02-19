
#include "functions.h"
#include "../led/led.h"

// vector size
#define SIZE_N 5

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

extern unsigned int funzione1(unsigned char *VETT, unsigned int n);


void key1_pressed(void) {
	
}

void key2_pressed(void) {
	
}

void int0_pressed(void) {
	
}

void timer0_tick() {
	
}

void timer1_tick() {
	
}

void timer2_tick() {
	
}

void timer3_tick() {
	
}

void joy_up_pressed() {
	
}


void call_ASM_function(void) {
	
}

