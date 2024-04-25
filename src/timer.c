#include <stdio.h>
#include <stdbool.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "timer.h"
#include "led.h"
#include "serial.h"
#include "command.h"
#include "menu.h"
#include "device.h"

// 8-bit timer. Used for PWM-value on the LED.
void timer2Init() {
    TCCR2A |= (1 << WGM21) | (1 << WGM20); // Enable Fast PWM mode.
    TCCR2B |= (1 << CS22); // Set prescaler to 64.
    TCCR2A |= (1 << COM2B1); // The COM2B1 control the PWM of the digital pin 3.
    OCR2A = MAX_POWER_VALUE; // Set the top value for the timer.
    OCR2B = MIN_POWER_VALUE; // Set the duty cycle to 0.
};

// Delayfunction in milliseconds, used to ramp the LED-effect.  
void delayMs(uint16_t ms) {
    unsigned char oldSreg = SREG; // Save the status register.
    cli(); // Disable interrupts.
    while (ms) {
        _delay_ms(1);
        ms--;
    }
    SREG = oldSreg; // Restore the status register.
};