#ifndef LED_H_
#define LED_H_

// LED macros
#define LED_PIN 3 // PD3 (Arduino pin 3)
#define LED_ON PORTD |= (1 << LED_PIN)
#define LED_OFF PORTD &= ~(1 << LED_PIN)
#define LED_TOGGLE PORTD ^= (1 << LED_PIN)

// Button macros
#define BUTTON_PIN 5 // PD5 (Arduino pin 5)
#define BUTTON_PIN_REGISTER PIND

void ledToggle();
void setLedOn(bool ledOn);

#endif // _LED_H_