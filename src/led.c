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
volatile bool ledTimerOn = false;
volatile uint8_t currentPwmValue = MIN_POWER_VALUE; // Default start-PWM value.

void ledToggle() {
    ledOn = !ledOn; // Toggle LED boolean.
    setLedOn(ledOn);
}

void setLedBrightness(uint8_t pwmValue) {
    LED_PWM_VALUE = pwmValue;  // Using Timer2 for PWM.
    currentPwmValue = pwmValue; // Set the current PWM value.
};

void ledRampTime(uint16_t timeMs) {
    // Convert integer to string.
    char timeString[PRINTOUT_RANGE];
    sprintf(timeString, "%d", timeMs);

    // Calculate frequency from timeMs.
    float frequency = 1.0 / (timeMs / 1000.0); // Convert timeMs to frequency in Hz.
    if(timeMs <= 1040){
            switchPrescaler(PRESCALER_256); // If milliseconds are set to 1040 or below, set prescaler to 256.
        } else {
            switchPrescaler(PRESCALER_1024); // If milliseconds are set above 1040, set prescaler to 1024.
        }
    adjustTimerFrequency(frequency); // Adjust timer frequency.

    uartPutString("LED Ramping started... ");
    uartPutChar('\n');
    for (uint16_t i = 0; i < MAX_POWER_VALUE; i++) {
        setLedBrightness(i); // Ramp up the PWM value.
        uartPutInt(i);
        uartPutChar('\n');
        _delay_ms(10);
    }
    for (uint16_t i = MAX_POWER_VALUE; i > MIN_POWER_VALUE; i--) {
        setLedBrightness(i); // Ramp down the PWM value.
        uartPutInt(i);
        uartPutChar('\n');
        _delay_ms(10);
    }
}

void pwmLedOn() {
    LED_PWM_VALUE = currentPwmValue;
}

void pwmLedOff() {
    LED_PWM_VALUE = MIN_POWER_VALUE;
}

void setLedOn(bool ledOn) {
    if(ledOn) {
        pwmLedOn();
    } else {
        pwmLedOff();
    }
};