#include <avr/io.h>
#include <stdio.h>
#include <stdbool.h>
#include "led.h"
#include "serial.h"
#include "device.h"
#include "timer.h"

volatile bool ledTimer = false; 

void ledToggle() {
    PORTD ^= (1 << LED_PIN);
};

void ledAdcValue(uint16_t adcValue) {
    // Map the ADC value from the 0-1023 scale to the 0-255 scale.
    uint8_t ledValue = (adcValue / 1024.0) * 255;
    // Write the value to the LED pin.
    OCR2B = ledValue; 
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