#ifndef LED_H_
#define LED_H_

#include <stdbool.h>
#include <stdlib.h>

// LED macros
#define LED_PIN PD3 // (Arduino pin 3)
#define LED_ON PORTD |= (1 << LED_PIN)
#define LED_OFF PORTD &= ~(1 << LED_PIN)
#define LED_TOGGLE PORTD ^= (1 << LED_PIN)

// String buffersize
#define PRINTOUT_RANGE 5

extern bool ledOn;

void ledToggle();
void setLedOn(bool ledOn);

#endif // _LED_H_