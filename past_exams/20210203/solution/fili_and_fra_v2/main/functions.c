
#include "functions.h"
#include "../led/led.h"

#define SIZE_N 300

volatile uint8_t valore_iniziale;
static int pointer_vett = 0;
static uint32_t tempi_variazioni[SIZE_N];

volatile uint8_t joystick_now;
volatile uint32_t time_before = 0;

// 0 monitor, 1 acquisizione
volatile uint8_t state = 0;
volatile uint32_t result = 0;

static uint8_t blink = 0;

unsigned char duty_cycle(unsigned char valore_iniziale, unsigned int tempo_totale, unsigned int tempi_variazioni[], unsigned char numero_variazioni);


void joystick_up_pressed(void) {
	if (joystick_now == 0) {
		joystick_now = 1;
		
		if (state == 1) {
			// funzione per calcolo tempo release
			count_time();
		}
	}
}

void joystick_up_released(void) {
	if (joystick_now == 1) {
		joystick_now = 0;
		
		if (state == 1) {
			// funzione per calcolo tempo release
			count_time();
		}
	}
}

void count_time(void) {
	uint32_t time;
	
	disable_timer(3);
	time = LPC_TIM3->TC;
	enable_timer(3);
	
	tempi_variazioni[pointer_vett] = time - time_before;
	pointer_vett++;
	
	time_before = time;
	
	if (pointer_vett == 5) {
		interrupt_acquisizione();
	}
}

void key2_pressed(void) {
	if (state == 0) {
		state = 1 - state;
		
		valore_iniziale = joystick_now;
		pointer_vett = 0;
		time_before = 0;
		
		init_timer(3, 25000000);
		enable_timer(3);
		
		LED_Out(255);
	}
}

void interrupt_acquisizione() {
	if (state == 1) {
		state = 0;
		
		disable_timer(3);
		
		// call ASM
		call_ASM_function();
	}
}

void call_ASM_function(void) {
	uint32_t total_time = 0;
	
	total_time = LPC_TIM3->TC;
	
	result = duty_cycle(valore_iniziale, total_time, tempi_variazioni, pointer_vett);
	
	init_timer(2, 50000000);
	enable_timer(2);
}

void timer2_tick(void) {
	if (blink == 0) {
		// numero variazioni
		
		LED_Out(pointer_vett);
		LED_On(7);
		blink = 1;
	} else {
		// duty cycle
		LED_Out(result);
		LED_Off(7);
		blink = 0;
	}
}

