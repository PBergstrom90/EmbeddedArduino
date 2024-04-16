#ifndef LED_H_
#define LED_H_

#include <stdbool.h>
#include <stdlib.h>

#define LED_ON PORTD |= (1 << LED_PIN)
#define LED_OFF PORTD &= ~(1 << LED_PIN)
#define LED_TOGGLE PORTD ^= (1 << LED_PIN)
#define MIN_POWER_VALUE 0
#define MAX_POWER_VALUE 255

extern bool ledOn;
extern volatile bool ledTimer;  
extern volatile uint8_t currentDutyCycle;

void ledToggle();
void setLedBrightness(uint8_t dutyCycle);
void ledPowerValue(uint8_t value, uint16_t timeMs);
void setLedOn(bool ledOn);

#endif // _LED_H_