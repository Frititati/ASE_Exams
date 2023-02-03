
#ifndef __FUNCTIONS_H
#define __FUNCTIONS_H

#include "LPC17XX.h"
#include "../timer/timer.h"

void reset(void);
void j_up_press(void);
void j_down_press(void);
void j_select_press(void);
void call_count(void);
void timer0_tick(void);

#endif
