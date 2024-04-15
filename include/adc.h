#ifndef ADC_H
#define ADC_H

#include <stdio.h>
#include <avr/io.h>

extern volatile bool adcToggle;
extern volatile bool adcReadState; 
extern volatile bool adcPrintState;

void adcLoop();
void adcInit();
float adcRead();
void adcPrint(float millivolts);
void adcConvert();

#endif // DEVICE_H