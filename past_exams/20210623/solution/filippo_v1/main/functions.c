
#include "functions.h"
#include "../led/led.h"

#define SIZE_N 50

// set to volatile such that the watch window can work correctly
volatile uint8_t VAR = 0;
static uint8_t VAR_COMPARE = 99;
static int pointer_vett = 0;
static int display_lock = 0;
static unsigned char VETT[SIZE_N];

extern unsigned int sopra_la_media(unsigned char *VETT, unsigned int n);

void reset(void) {
	VAR = 0;
}

void j_up_press(void) {
	if (display_lock == 0) {
		VAR++;
		update_led_value();
	}
}

void j_left_press(void) {
	if (display_lock == 0) {
		VAR--;
		update_led_value();
	}
}

void j_select_press(void) {
	if (display_lock == 0) {
		VAR = 0;
		update_led_value();
	}
	display_lock = 0;
}

void update_led_value(void) {
	LED_Out(VAR);
}

void int0_press(void) {
	int result = 0;
	if (VAR_COMPARE == VAR || (pointer_vett + 1) == SIZE_N) {
		result = sopra_la_media(VETT, pointer_vett);
		pointer_vett = 0;
		LED_Out(result);
		display_lock = 1;
	} else {
		VAR_COMPARE = VAR;
		VETT[pointer_vett] = VAR;
		pointer_vett++;
	}
	VAR = 0;
}

