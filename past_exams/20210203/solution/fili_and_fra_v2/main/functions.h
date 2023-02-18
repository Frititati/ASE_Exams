
#ifndef __FUNCTIONS_H
#define __FUNCTIONS_H

#include "LPC17XX.h"
#include "../timer/timer.h"

void joystick_up_pressed(void);
void joystick_up_released(void);

void interrupt_acquisizione(void);
void timer2_tick(void);

void key1_pressed(void);
void key2_pressed(void);
void int0_pressed(void);

void call_ASM_function(void);

void count_time(void);

#endif
