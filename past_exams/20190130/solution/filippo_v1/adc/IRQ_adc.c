
#include "lpc17xx.h"
#include "adc.h"

extern unsigned short volume;

// const int freqs[8]={2120,1890,1684,1592,1417,1263,1125,1062};

void ADC_IRQHandler(void) {
  AD_current = ((LPC_ADC->ADGDR>>4) & 0xFFF);
  if(AD_current != AD_last){
    volume = (AD_current * 4)/0xFFF;
    AD_last = AD_current;
  }
}
