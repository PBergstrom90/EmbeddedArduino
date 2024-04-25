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

// 16-bit timer. Used to keep track of the buttoncounter.
void timer1Init() {
    TCCR1A = 0; // Set default values
    TCCR1B = 0;
    TCCR1B |= (1 << CS12) | (1 << CS11); // Enable CS12 and CS11 for Counter Mode.
    BUTTON_COUNTER = 0; // Set the timer to 0.
};

// 8-bit timer. Used for buttonCounterPrint.
void timer2Init() {
    TCCR2A = 0; // Set default values
    TCCR2B = 0;
    TCCR2B |= (1 << CS22) | (1 << CS21); // Set prescaler to 256.
    TIMSK2 = (1 << TOIE2); // Enable overflow interrupt.
};

// Used for timing the buttonCounterPrint-function. 
// Not the best solution, since it clutters the interrupt. But it works for now.
ISR(TIMER2_OVF_vect) {
    static uint16_t count = 0;
    count++;
    if(count >= 255) { // Approximately 1 second.
        count = 0;
        if(buttonTimer){
            buttonPrint = true;
        }
    }
};