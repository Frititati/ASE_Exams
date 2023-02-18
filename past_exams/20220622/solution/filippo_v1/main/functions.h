
#ifndef __FUNCTIONS_H
#define __FUNCTIONS_H

#include "LPC17XX.h"
#include "../timer/timer.h"

void set_var(uint32_t temp);

void timer1_tick(void);
void timer2_tick(void);

void key1_pressed(void);
void key2_pressed(void);
void int0_pressed(void);

void call_ASM_function(void);


#endif