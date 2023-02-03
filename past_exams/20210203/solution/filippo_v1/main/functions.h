
#ifndef __FUNCTIONS_H
#define __FUNCTIONS_H

#include "LPC17XX.h"
#include "../timer/timer.h"

void reset(void);
void key2_press(void);
void timer3_tick(void);
void change_to_monitor(void);
void j_up_press(void);

typedef enum stateType {
    StateMonitor = 0,
    StateAcquisizione = 1
} STATETYPE;



#endif
