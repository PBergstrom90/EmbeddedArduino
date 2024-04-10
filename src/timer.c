#include <stdio.h>
#include <stdbool.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include "timer.h"
#include "led.h"
#include "serial.h"
#include "command.h"
#include "menu.h"

volatile bool timer1Enabled = false;

void timerInit() {
    // Timer 1 initialization
    TCCR1A = 0; // Set default values
    TCCR1B = 0;
    TCCR1B |= (1 << WGM12); // Enable CTC mode (Clear Timer on Compare Match).
    TCCR1B |= (1 << CS11) | (1 << CS10); // Enable CS11 and CS10 for Prescaler 64.
    OCR1A = 50000; // Timer counter value for 200ms compare match (16Mhz/64/5Hz).
    TIMSK1 |= (1 << OCIE1A); // Enable compare match interrupt.
    sei();
};

ISR(TIMER1_COMPA_vect) {
    if(timer1Enabled) {
        ledToggle();
    }
}