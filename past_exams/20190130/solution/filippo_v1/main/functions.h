
#ifndef __FUNCTIONS_H
#define __FUNCTIONS_H

#include "LPC17XX.h"
#include "../timer/timer.h"

void reset(void);
void key2_press(void);
void int0_press(void);
void j_down_press(void);
void led_timer_tick(void);
void led_timer_start(void);
void led_timer_stop(void);

#endif
