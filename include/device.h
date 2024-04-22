#ifndef DEVICE_H
#define DEVICE_H

#include <stdio.h>
#include <avr/io.h>

#define BUTTON_PIN 5 // PD5 (Arduino pin 5)
#define BUTTON_PIN_REGISTER PIND // PIND register

void setup();
void onButtonPressed();
bool isButtonPressed();

#endif // DEVICE_H