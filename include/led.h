#ifndef LED_H_
#define LED_H_

// LED macros
#define LED_PIN 3 // PD3 (Arduino pin 3)
#define LED_ON PORTD |= (1 << LED_PIN)
#define LED_OFF PORTD &= ~(1 << LED_PIN)
#define LED_TOGGLE PORTD ^= (1 << LED_PIN)
#define LED_PWM_VALUE OCR2B

// PWM Macros
#define MIN_POWER_VALUE 0
#define MAX_POWER_VALUE 255

#include <stdbool.h>

extern volatile bool ledTimer;  

void ledToggle();
void ledPowerValue(uint8_t value);
void setLedOn(bool ledOn);

#endif // _LED_H_