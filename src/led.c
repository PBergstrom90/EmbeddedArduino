#include <avr/io.h>
#include <stdio.h>
#include <stdbool.h>
#include "led.h"
#include "serial.h"
#include "device.h"
#include "timer.h"

bool ledOn = false;
volatile bool ledTimer = false; 

void ledToggle() {
    PORTD ^= (1 << LED_PIN);
};

void ledPowerValue(uint8_t value) {
    // Convert integer to string.
    char valueString[5];
    sprintf(valueString, "%d", value);
    if(value >= MIN_POWER_VALUE && value <= 127){
        setLedOn(false);
    } else if(value >= 128 && value <= MAX_POWER_VALUE){
        setLedOn(true);
    }
    uartPutString("LED value is: ");
    uartPutString(valueString);
    uartPutChar('\n');
};

void setLedOn(bool ledOn) {
    if(ledOn) {
        PORTD |= (1 << LED_PIN);
    } else {
        PORTD &= ~(1 << LED_PIN);
    }
}