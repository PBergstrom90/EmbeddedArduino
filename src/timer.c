#include <stdio.h>
#include <stdbool.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include "timer.h"
#include "led.h"
#include "serial.h"
#include "command.h"
#include "menu.h"
#include "device.h"

volatile bool timer1Enabled = false;
volatile bool timer2Enabled = false;
volatile uint16_t timer2Counter = 0;

// 16-bit timer.
void timer1Init() {
    TCCR1A = 0; // Set default values
    TCCR1B = 0;
    TCCR1B |= (1 << WGM12); // Enable CTC mode (Clear Timer on Compare Match).
    TCCR1B |= (1 << CS11) | (1 << CS10); // Enable CS11 and CS10 for Prescaler 64.
    OCR1A = 50000; // Timer counter value for 200ms compare match (16Mhz/64/5Hz).
    TIMSK1 |= (1 << OCIE1A); // Enable compare match interrupt.
};

// 8-bit timer.
void timer2Init() {
    TCCR2A = 0; // Set default values
    TCCR2B = 0;
    TCCR2B |= (1 << WGM22); // Enable CTC mode (Clear Timer on Compare Match).
    TCCR2B |= (1 << CS22) | (1 << CS21); // Enable CS22 for Prescaler 256.
    OCR2A = 156; // Timer counter value for 10ms compare match (16Mhz/256/100Hz).
    TIMSK2 |= (1 << OCIE2A); // Enable compare match interrupt.
};

ISR(TIMER1_COMPA_vect) {
    if(timer1Enabled) {
        ledToggle();
    }
}

ISR(TIMER2_COMPA_vect) {
    timer2Counter++;
    if(timer2Counter >= 100) { // 100 * 10ms = 1s
        if(timer2Enabled) {
            adcRead();
        }
        timer2Counter = 0;
    }
}