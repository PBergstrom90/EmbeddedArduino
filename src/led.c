#include <avr/io.h>
#include <stdio.h>
#include <stdbool.h>
#include "led.h"
#include "serial.h"
#include "device.h"
#include "timer.h"
#include "adc.h"

bool ledOn = false;
volatile bool ledTimer = false;
volatile uint8_t currentDutyCycle = 0;

void ledToggle() {
    LED_TOGGLE;
};

void setLedBrightness(uint8_t dutyCycle) {
    OCR2A = dutyCycle;  // Using Timer2 for PWM.
};

void ledPowerValue(uint8_t value, uint16_t timeMs) {
    // Convert integer to string.
    char valueString[5];
    char timeString[5];
    sprintf(valueString, "%d", value);
    sprintf(timeString, "%d", timeMs);

    // Calculate frequency from timeMs
    float frequency = 1.0 / (timeMs / 1000.0); // Convert timeMs to frequency in Hz
    
    // Adjust timer frequency
    adjustTimerFrequency(frequency);
    
    // Set PWM duty cycle.
    value = currentDutyCycle;
    
    uartPutString("LED powervalue is: ");
    uartPutString(valueString);
    uartPutChar('\n');
    uartPutString("LED timer value is: ");
    uartPutString(timeString);
    uartPutChar('\n');
}

void setLedOn(bool ledOn) {
    if(ledOn) {
        LED_ON;
    } else {
        LED_OFF;
    }
};