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

volatile uint16_t overflowCount = 0; // Global variable to store the number of timeroverflows.

// 8-bit timer. Used for buttonCounterPrint.
void timer0Init() {
    TCCR0A = 0;
    TCCR0B = 0;
    TCCR0B |= (1 << CS02); // Set prescaler to 256.
    TIMSK0 = (1 << TOIE0); // Enable overflow interrupt.
};

ISR(TIMER0_OVF_vect) {
    static uint16_t count = 0;
    count++;
    if(count >= 255) { // Approximately 1 second.
        count = 0;
        if(buttonTimer){
            buttonPrint = true;
        }
    }
};

// 16-bit timer. Used to adjust the LED-toggle frequency.
void timer1Init() {
    TCCR1A = 0; // Set default values
    TCCR1B = 0;
    TCCR1B |= (1 << CS12) | (1 << CS11); // Enable CS12 and CS11 for Counter Mode.
    BUTTON_COUNTER = 0; // Set the timer to 0.
};