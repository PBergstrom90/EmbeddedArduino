#include <avr/io.h>
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
};

void setLedBrightness(uint8_t pwmValue) {
    LED_PWM_VALUE = pwmValue;  // Using Timer2 for PWM.
    currentPwmValue = pwmValue; // Set the current PWM value.
};

void ledPowerValue(uint8_t pwmValue, uint16_t timeMs) {
    // Convert integer to string.
    char valueString[PRINTOUT_RANGE];
    char timeString[PRINTOUT_RANGE];
    sprintf(valueString, "%d", pwmValue);
    sprintf(timeString, "%d", timeMs);

    // Calculate frequency from timeMs.
    float frequency = 1.0 / (timeMs / 1000.0); // Convert timeMs to frequency in Hz.
    if(timeMs <= PRESCALER_MAX_TIME_MS) {
        if(timeMs <= 1040){
            switchPrescaler(PRESCALER_256); // If milliseconds are set to 1040 or below, set prescaler to 256.
        } else {
            switchPrescaler(PRESCALER_1024); // If milliseconds are set above 1040, set prescaler to 1024.
        }
    } else if (timeMs <= MAX_TIME_MS) { // If timeMs is set above 4194 milliseconds (max timevalue for max prescaler), increment overflowCount.
        // Calculate the number of overflows needed.
        overflowCount = timeMs / PRESCALER_MAX_TIME_MS;
        if (timeMs % PRESCALER_MAX_TIME_MS != 0) {
            overflowCount++;
        }
        // Set the prescaler to 1024 and the frequency to correspond to 4194 ms.
        switchPrescaler(PRESCALER_1024);
        frequency = 1.0 / (PRESCALER_MAX_TIME_MS / 1000.0);
    }
    
    adjustTimerFrequency(frequency); // Adjust timer frequency.
    setLedBrightness(pwmValue); // Set PWM duty cycle.
    
    uartPutString("LED powervalue is: ");
    uartPutString(valueString);
    uartPutChar('\n');
    uartPutString("LED timer value is: ");
    uartPutString(timeString);
    uartPutChar('\n');
};

void pwmLedOn() {
    LED_PWM_VALUE = currentPwmValue;
};

void pwmLedOff() {
    LED_PWM_VALUE = MIN_POWER_VALUE;
};

void setLedOn(bool ledOn) {
    if(ledOn) {
        pwmLedOn();
    } else {
        pwmLedOff();
    }
};