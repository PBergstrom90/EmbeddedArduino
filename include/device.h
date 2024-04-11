#ifndef DEVICE_H
#define DEVICE_H

#include <stdio.h>
#include <avr/io.h>

extern volatile bool adcToggle;

void setup();
void buttonPressed();
void adcInit();
void adcRead();
void adcConvert();

#endif // DEVICE_H