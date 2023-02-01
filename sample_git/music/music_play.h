
#ifndef __MUSIC_PLAY_H
#define __MUSIC_PLAY_H

#include "music.h"

typedef enum playTypes
{
	PlayTypeClick = 1,
	PlayTypeFood = 2,
	PlayTypeLeave = 3,
	PlayTypeCuddle = 4,
	PlayTypeNone = 0xFF
} PLAYTYPES;


void timer2Interrupt(void);
void play(PLAYTYPES type);

#endif
