
#include "lpc17xx.h"
#include "RIT.h"
#include "../led/led.h"
#include "../timer/timer.h"
// #include "../adc/adc.h"
#include "../main/functions.h"
#define N 5

extern uint8_t stateINT0;
extern uint8_t stateKEY1;
extern uint8_t stateKEY2;

void RIT_IRQHandler (void)
{
	static int left, right, up, down, select;
	static int pressedINT0=0;	
	static int pressedKEY1=0;	
	static int pressedKEY2=0;
	
	//GESTIONE BUTTON CON INTERRUPT E DEBOUNCING. RICHIAMATO AD OGNI HANDLER DEI VARI BUTTON
	//I vari case sono dei multipli del RIT timer. (ex per quanti multipli di RIT ho premuto il pulsante)

	
	//Ricordarsi di resettare i timer ove serve da INTERRUPT di BOTTONE
	if((LPC_PINCON->PINSEL4 & (1 << 24)) == 0){
		pressedKEY2++;
		if((LPC_GPIO2->FIOPIN & (1<<12)) == 0){   //key2
			reset_RIT();
			switch(pressedKEY2){
				case 1:
					
					//COSA FARE PREMUTO 50 MS
					key2_pressed();
					
					break;
				default:
					
					break;
			}
		}
		else {	/* button released */
			pressedKEY2=0;
			
			//COSA FARE AL RILASCIO?
			
			reset_RIT();
			NVIC_EnableIRQ(EINT2_IRQn);							 /* disable Button interrupts			*/
			LPC_PINCON->PINSEL4    |= (1 << 24);     /* External interrupt 0 pin selection */
		}
	}
	
	
	if((LPC_PINCON->PINSEL4 & (1 << 22)) == 0){
		pressedKEY1++;
		if((LPC_GPIO2->FIOPIN & (1<<11)) == 0){   //key1
			reset_RIT(); // si può rimuovere
			switch(pressedKEY1){
				case 1:
					
					//COSA FARE PREMUTO 50 MS?
					key1_pressed();
					
					break;
				default:
					break;
			}
		}
		else {	/* button released */
		
			pressedKEY1=0;
			
			//COSA FARE AL RILASCIO?
			
			reset_RIT();
			NVIC_EnableIRQ(EINT1_IRQn);							 /* disable Button interrupts			*/
			LPC_PINCON->PINSEL4    |= (1 << 22);     /* External interrupt 0 pin selection */
		}
	}
	
	
	if((LPC_PINCON->PINSEL4 & (1 << 20)) == 0){
		pressedINT0++;
		if((LPC_GPIO2->FIOPIN & (1<<10)) == 0){   //int0
			reset_RIT();
			switch(pressedINT0){
				case 1:
					
					//COSA FARE PREMUTO 50 MS
					int0_pressed();
					
					break;
				default:
					break;
			}
		}
		else {	/* button released */
			pressedINT0=0;
			
			//COSA FARE AL RILASCIO?
			
			reset_RIT();
			NVIC_EnableIRQ(EINT0_IRQn);							 /* disable Button interrupts			*/
			LPC_PINCON->PINSEL4    |= (1 << 20);     /* External interrupt 0 pin selection */
		}
	}
	
	//FINE GESTIONE BUTTON DEBOUNCING
	//GESTIONE JOYSTICK
	//25 select 26 down 27 left 28 right 29 up
	
	if((LPC_GPIO1->FIOPIN & (1<<25)) == 0){	
		/* Joytick SELECT pressed */
		select++;
		switch(select){
			case 1:
				
				//COSA FARE SELECT
				joy_select_pressed();
				
				break;
			default:
				break;
		}
	}
	else{
		select=0;
		
		//COSA FARE RILASCIO
	}
	
	if((LPC_GPIO1->FIOPIN & (1<<26)) == 0){	
		/* Joytick SELECT pressed */
		down++;
		switch(down){
			case 1:
				
				//COSA FARE DOWN
				joy_down_pressed();
			
				break;
			default:
				break;
		}
	}
	else
	{
		down=0;
		
		//COSA FARE RILASCIO
	}
	
	if((LPC_GPIO1->FIOPIN & (1<<27)) == 0){	
		/* Joytick LEFT pressed */
		left++;
		switch(left){
			case 1:
				
				//COSA FARE LEFT
			
				break;
			default:
				break;
		}
	}
	else
	{
			left=0;
			//COSA FARE RILASCIO
		
		
	}
	
	if((LPC_GPIO1->FIOPIN & (1<<28)) == 0){	
		/* Joytick RIGHT pressed */
		right++;
		switch(right){
			case 1:
				
				//COSA FARE RIGHT
			
				break;
			default:
				break;
		}
	}
	else
	{
			right=0;
		//COSA FARE RILASCIO
	}
	
	if((LPC_GPIO1->FIOPIN & (1<<29)) == 0){	
		/* Joytick UP pressed */
		up++;
		switch(up){
			case 1:
				
				//COSA FARE UP
				joy_up_pressed();
			
				break;
			default:
				break;
		}
	}
	else
	{
			//COSA FARE RILASCIO
			up=0;
	}
	
	// ADC_start_conversion();
	//Nel caso si mette una static per la gestione dell'adc e ogni quanti 50xN millisecondi aggiornare il tutto.
	
	LPC_RIT->RICTRL |= 0x1;	/* clear interrupt flag */
	
	return;
}

/*
extern void LED_seconds(int readValue)
{
	int i=0;
	for(;i<8;i++) LED_Off(i);
	switch(readValue)
	{
		case(1):LED_On(0);break;
		case(2):LED_On(4);break;
		case(3):LED_On(6);break;
		case(4):LED_On(7);break;
		case(5):LED_On(1);break;
		case(6):LED_On(2);break;
		case(7):LED_On(5);break;
		case(8):LED_On(3);break;
		default:LED_On(0);LED_On(2);LED_On(4);LED_On(6);break;

	}
}
*/
