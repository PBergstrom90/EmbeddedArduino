#include <avr/io.h>
#include <stdio.h>
#include "led.h"
#include "serial.h"

void ledToggle() {
    PORTD ^= (1 << LED_PIN);
};  

void ledPowerValue(uint8_t value) {
    // Convert integer to string.
    char valueString[5];
    sprintf(valueString, "%d", value);
    if(value >= MIN_POWER_VALUE && value <= 127){
        // Turn off the LED.
        PORTD &= ~(1 << LED_PIN);
    } else if(value >= 128 && value <= MAX_POWER_VALUE){
        // Turn on the LED.
        PORTD |= (1 << LED_PIN);
    }
    // Print a message to the serial monitor.
    uartPutString("LED value is: ");
    uartPutString(valueString);
    uartPutChar('\n');
};