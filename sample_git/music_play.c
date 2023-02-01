
#include "music.h"
#include "LPC17XX.h"

void playOneNote() {
	static int currentNote = 10;
	static int ticks = 0;
	
	ADC_start_conversion();
	
	if(!isNotePlaying())
	{
		ticks = 0;
		playNote(song[currentNote++]);
	}
}