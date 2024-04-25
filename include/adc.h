#ifndef ADC_H
#define ADC_H

#include <stdio.h>
#include <avr/io.h>

#define MILLIVOLTS_100 100
#define MILLIVOLTS_1000 1000
#define MILLIVOLTS_2000 2000
#define MILLIVOLTS_3000 3000
#define MILLIVOLTS_4000 4000
#define MILLIVOLTS_5000 5000

extern volatile bool adcToggle;
extern volatile bool adcReadState; 
extern volatile bool adcPrintState;

void adcLoop();
void adcInit();
float adcRead();
void adcPrint(float millivolts);
void adcConvert();

#endif // DEVICE_H