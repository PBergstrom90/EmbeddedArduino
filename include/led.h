#ifndef LED_H_
#define LED_H_

#include <stdbool.h>
#include <stdlib.h>

// LED macros
#define LED_PIN PD3 // (Arduino pin 3)
#define LED_ON PORTD |= (1 << LED_PIN)
#define LED_OFF PORTD &= ~(1 << LED_PIN)
#define LED_TOGGLE PORTD ^= (1 << LED_PIN)
#define LED_PWM_VALUE OCR2B

// PWM macros
#define MIN_POWER_VALUE 0
#define MAX_POWER_VALUE 255

// String buffersize
#define PRINTOUT_RANGE 5

extern bool ledOn;
extern volatile bool ledTimerOn;  
extern volatile uint8_t currentPwmValue;

void ledToggle();
void setLedBrightness(uint8_t pwmValue);
void ledPowerValue(uint8_t pwmValue, uint16_t timeMs);
void setLedOn(bool ledOn);

#endif // _LED_H_