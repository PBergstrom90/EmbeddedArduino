#ifndef DEVICE_H
#define DEVICE_H

#include <stdio.h>
#include <avr/io.h>

void setup();
void onButtonPressed();
bool isButtonPressed();

#endif // DEVICE_H