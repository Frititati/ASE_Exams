
#ifndef __ADC_H
#define __ADC_H

/* lib_adc.c */
void ADC_init (void);
void ADC_start_conversion (void);

/* IRQ_adc.c */
void ADC_IRQHandler(void);

static unsigned short AD_current;   
static unsigned short AD_last = 0xFF;

#endif
