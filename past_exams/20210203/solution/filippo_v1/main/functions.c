
#include "functions.h"
#include "../led/led.h"

#define SIZE_N 100

// set to volatile such that the watch window can work correctly
volatile STATETYPE state = StateMonitor;
volatile uint8_t valore_iniziale = 0;
volatile uint8_t J_up = 99;
volatile uint8_t J_up_prev = 0;

static uint32_t tempi_variazioni[SIZE_N];
static int pointer_vett = 0;

extern unsigned int sopra_la_media(unsigned char *VETT, unsigned int n);

void reset(void) {
	valore_iniziale = 0;
	pointer_vett = 0;
}

void key2_press(void) {
	if (state == StateMonitor) {		
		state = StateAcquisizione;
		valore_iniziale = J_up;
		j_up_press = J_up;
		init_timer(3, 25000000);
		enable_timer(3);
	}
}

void timer3_tick() {
	if (state == StateAcquisizione) {
		change_to_monitor();
	}
	disable_timer(3);
}

void irq_interrupt(void) {
	if (state == StateAcquisizione) {
		tempi_variazioni[pointer_vett] = J_up;
		pointer_vett++;
	}
}

void change_to_monitor(void) {
	
}

