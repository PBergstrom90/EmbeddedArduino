#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>
#include <stdbool.h>
#include "led.h"
#include "serial.h"
#include "device.h"
#include "timer.h"

bool ledOn = false;
volatile uint8_t currentPwmValue = MIN_POWER_VALUE; // Default start-PWM value.

void ledToggle() {
    ledOn = !ledOn; // Toggle LED boolean.
    setLedOn(ledOn);
};

void setLedBrightness(uint8_t pwmValue) {
    LED_PWM_VALUE = pwmValue;  // Using Timer2 for PWM.
    currentPwmValue = pwmValue; // Set the current PWM value.
};

// Ramp the LED up and down. Time-input is counted up and then same time down.
void ledRampTime(short int timeMs) {
    short int interval = timeMs / MAX_POWER_VALUE;
    uartPutString("LED Ramping started... ");
    uartPutChar('\n');
    for (uint16_t i = 0; i < MAX_POWER_VALUE; i++) {
        setLedBrightness(i);
        delayMs(interval);
    }
    for (uint16_t i = MAX_POWER_VALUE; i > MIN_POWER_VALUE; i--) {
        setLedBrightness(i);
        delayMs(interval);
    }
    uartPutString("LED Ramping finished.");
    uartPutChar('\n');
};

void setLedOn(bool ledOn) {
    if(ledOn) {
        pwmLedOn();
    } else {
        pwmLedOff();
    }
};

void pwmLedOn() {
    LED_PWM_VALUE = currentPwmValue;
};

void pwmLedOff() {
    LED_PWM_VALUE = MIN_POWER_VALUE;
};