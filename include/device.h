#ifndef DEVICE_H
#define DEVICE_H

#include <stdio.h>
#include <avr/io.h>

extern volatile bool adcToggle;
extern volatile bool adcReadState; 
extern volatile bool adcPrintState;

void setup();
void buttonPressed();
void adcInit();
void adcRead();
void adcPrint(uint32_t timerValue, float millivolts);
void adcConvert();

#endif // DEVICE_H