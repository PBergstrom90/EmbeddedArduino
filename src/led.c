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
volatile uint8_t currentPwmValue = 0;

void ledToggle() {
    ledOn = !ledOn; // Toggle LED state
    setLedOn(ledOn);
}

void setLedBrightness(uint8_t pwmValue) {
    LED_PWM_PIN = pwmValue;  // Using Timer2 for PWM.
    currentPwmValue = pwmValue; // Set the current PWM value
};

void ledPowerValue(uint8_t pwmValue, uint16_t timeMs) {
    // Convert integer to string.
    char valueString[5];
    char timeString[5];
    sprintf(valueString, "%d", pwmValue);
    sprintf(timeString, "%d", timeMs);

    // Calculate frequency from timeMs
    float frequency = 1.0 / (timeMs / 1000.0); // Convert timeMs to frequency in Hz

    pwmValue = currentPwmValue; // Set the current PWM value
    adjustTimerFrequency(frequency); // Adjust timer frequency

    setLedBrightness(currentPwmValue); // Set PWM duty cycle.
    
    uartPutString("LED powervalue is: ");
    uartPutString(valueString);
    uartPutChar('\n');
    uartPutString("LED timer value is: ");
    uartPutString(timeString);
    uartPutChar('\n');
}

void pwmLedOn() { 
    LED_PWM_PIN = currentPwmValue;
}

void pwmLedOff() {
    LED_PWM_PIN = 0;
}

void setLedOn(bool ledOn) {
    if(ledOn) {
        pwmLedOn();
    } else {
        pwmLedOff();
    }
};