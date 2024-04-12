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

// 16-bit timer.
void timer1Init() {
    TCCR1A = 0; // Set default values
    TCCR1B = 0;
    TCCR1A |= (1 << WGM11) | (1 << WGM10); // Enable Fast PWM mode, TOP is ICR1.
    TCCR1B |= (1 << WGM12) | (1 << WGM13); // Enable CTC mode (Clear Timer on Compare Match).
    TCCR1B |= (1 << CS12) | (1 << CS10); // Enable CS12 and CS10 for Prescaler 1024.
    ICR1 = 15652; // Timer counter value for 1 second overflow (16Mhz/1024/1Hz).
    OCR1A = 3125; // Timer counter value for 200ms compare match (16Mhz/1024/5Hz).
    OCR1B = 1563; // Timer counter value for 100ms compare match B (16Mhz/1024/10Hz).
    TIMSK1 |= (1 << OCIE1A); // Enable compare match interrupt.
    TIMSK1 |= (1 << OCIE1B); // Enable compare match interrupt B.
    TIMSK1 |= (1 << TOIE1); // Enable overflow interrupt.  
};

ISR(TIMER1_COMPA_vect) {
    // Enable and disable the LED toggle-timer.
    if(ledTimer) {
        ledToggle();
    }
};

ISR(TIMER1_COMPB_vect) {
    // Enable and disable the ADC read state.
    if(adcToggle) {
        adcReadState = true;
    } else if (!adcToggle) {
        adcReadState = false;
    }
};

ISR(TIMER1_OVF_vect) {
    // Write ADC value to serial monitor every 1 second. Trigger the printstate to signal adc print.
    adcPrintState = true;
};

void switchTimerValue(uint32_t timerValue) {
    OCR1A = timerValue; // Set the new compare match value.
};

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