
#include "LPC17XX.h"
#include "music_play.h"
#include "../timer/timer.h"

static uint8_t notesPlayed;
static uint8_t currentPlayType = 0xFF;

static NOTE foodSong[] = {
	{a3, time_semicroma},
	{b3, time_semicroma},
	{c4, time_semicroma},
	{d4, time_croma},
	{c4, time_semicroma},
	{b3, time_semicroma},
	{a3, time_croma}
};

static NOTE leaveSong[] = {
	{c4, time_semicroma},
	{d4, time_semicroma},
	{e4, time_semicroma},
	{c4, time_semicroma},
	{e4, time_semicroma},
	{d4, time_semicroma},
	{c4, time_croma}
};

static NOTE cuddleSong[] = {
	{e4, time_semicroma},
	{d4, time_semicroma},
	{c4, time_semicroma},
	{d4, time_semicroma},
	{e4, time_semicroma},
	{e4, time_semicroma},
	{e4, time_croma},
	{d4, time_semicroma},
	{d4, time_semicroma},
	{d4, time_croma},
	{e4, time_semicroma},
	{g4, time_semicroma},
	{g4, time_semicroma}
};

void playClickNoise() {
	NOTE note_struct;
	note_struct.freq = f4;
	note_struct.duration = time_croma;
	playNote(note_struct);
}

void playFoodNoise(uint8_t at) {
	playNote(foodSong[at]);
}

void playLeaveNoise(uint8_t at) {
	playNote(leaveSong[at]);
}

void playCuddleNoise(uint8_t at) {
	playNote(cuddleSong[at]);
}

// this is probably wrong
void setSilence() {
	notesPlayed = 0;
	disable_timer(1);
	disable_timer(2);
}

void timer2Interrupt() {
	if (currentPlayType == PlayTypeClick) {
		currentPlayType = PlayTypeNone;
		setSilence();
	}
	if (currentPlayType == PlayTypeFood) {
		//TODO: set notes to 3
		if (notesPlayed < 8) {
			playFoodNoise(notesPlayed);
		} else {
			currentPlayType = PlayTypeNone;
			setSilence();
		}
	}
	if (currentPlayType == PlayTypeLeave) {
		//TODO: set notes to 5
		if (notesPlayed < 8) {
			playLeaveNoise(notesPlayed);
		} else {
			currentPlayType = PlayTypeNone;
			setSilence();
		}
	}
	if (currentPlayType == PlayTypeCuddle) {
		//TODO: set notes to 8
		if (notesPlayed < 13) {
			playCuddleNoise(notesPlayed);
		} else {
			currentPlayType = PlayTypeNone;
			setSilence();
		}
	}
	notesPlayed++;
}

void play(PLAYTYPES type) {
	if (currentPlayType != type) {
		// reset notes played because we want to play something different
		notesPlayed = 0;
		if ( type == PlayTypeClick) {
			currentPlayType = PlayTypeClick;
			playClickNoise();
		}
		if ( type == PlayTypeFood) {
			currentPlayType = PlayTypeFood;
			playFoodNoise(notesPlayed);
		}
		if ( type == PlayTypeLeave) {
			currentPlayType = PlayTypeLeave;
			playLeaveNoise(notesPlayed);
		}
		if ( type == PlayTypeCuddle) {
			currentPlayType = PlayTypeCuddle;
			playCuddleNoise(notesPlayed);
		}
	} else {
		// same type means we don't have to react
	}
	notesPlayed++;
}





