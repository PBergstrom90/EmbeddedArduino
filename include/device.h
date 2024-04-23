#ifndef DEVICE_H
#define DEVICE_H

#include <stdio.h>
#include <avr/io.h>

#define BUTTON_PIN 5 // PD5 (Arduino pin 5)
#define BUTTON_PIN_REGISTER PIND // PIND register
#define DEBOUNCE_DELAY 15 

enum ButtonState {
    BUTTON_RELEASED,
    BUTTON_PRESSED,
    BUTTON_DEBOUNCING
};

extern int buttonCounter;
extern bool buttonPrint;
extern bool buttonTimer;

void setup();
void onButtonPressed();
bool isButtonPressed();
void buttonCounterPrint();
enum ButtonState buttonDebounce(enum ButtonState btnState);

#endif // DEVICE_H