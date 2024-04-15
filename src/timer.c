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
#include "adc.h"

// 16-bit timer. Used to adjust the LED-toggle frequency.
void timer1Init() {
    TCCR1A = 0; // Set default values
    TCCR1B = 0;
    TCCR1A |= (1 << WGM11) | (1 << WGM10); // Enable Fast PWM mode.
    TCCR1B |= (1 << WGM12) | (1 << WGM13); // Enable CTC mode (Clear Timer on Compare Match).
    TCCR1B |= (1 << CS12) | (1 << CS10); // Enable CS12 and CS10 for Prescaler 1024.
    OCR1A = 3125; // Timer counter value for 200ms compare match (16Mhz/1024/5Hz).
    TIMSK1 |= (1 << OCIE1A); // Enable compare match interrupt.
};

// 8-bit timer. Used to count seconds for the ADC-printout.
void timer2Init() {
    TCCR2B |= (1 << CS22) | (1 << CS21) | (1 << CS20); // Set prescaler to 1024.
    TIMSK2 |= (1 << TOIE2); // Enable overflow interrupt.
};

// Adjustable delay from adcRead();
ISR(TIMER1_COMPA_vect) {
    if(ledTimer) {
        ledToggle();
    }
};

ISR(TIMER2_OVF_vect) {
    // Rough 1 second delay.
    static uint16_t count = 0;
    count++;
    if (count >= 61) { // Approximately 1 second (16MHz/1024/256 = 61.035 Hz).
        adcPrintState = true;
        count = 0;
    }
}

// Interrupt when ADC-conversion is complete.
ISR(ADC_vect) {
    if(adcToggle){
        adcReadState = true;
    } else {
        adcReadState = false;
    }
}

// Switch the compare match value for the timer to increase/decrease LED toggle frequency.
void switchTimerValue(uint32_t timerValue) {
    OCR1A = timerValue; // Set the new compare match value.
};

// Switch the prescaler for the timer, if necessary.
void switchPrescaler(uint16_t prescaler) {
    cli(); // Disable interrupts.
    TCCR1B &= ~((1 << CS10) | (1 << CS11) | (1 << CS12)); // Stop the timer.
    switch(prescaler) {
        case 1:
            TCCR1B |= (1 << CS10);
            break;
        case 8:
            TCCR1B |= (1 << CS11);
            break;
        case 64:
            TCCR1B |= (1 << CS11) | (1 << CS10);
            break;
        case 256:
            TCCR1B |= (1 << CS12);
            break;
        case 1024:
            TCCR1B |= (1 << CS12) | (1 << CS10);
            break;
        default:
            break;
    }
    sei(); // Enable interrupts.
    TCCR1B |= prescaler; // Restart the timer with the new prescaler.
};