#include <stdio.h>
#include <stdbool.h>
#include "device.h"
#include "led.h"
#include "command.h"
#include "serial.h"
#include "timer.h"
#include "menu.h"

volatile bool adcToggle = false;

void setup() {
    bool setupDone = false;    
    
    // Set LED pin as output.
    DDRD |= (1 << LED_PIN);
    // Set Button pin as input.
    DDRD &= ~(1 << BUTTON_PIN);
    // Enable pull-up resistor for Button pin. 
    // Because there is a 10k-Ohm resistor between 5V and the button.
    PORTD |= (1 << BUTTON_PIN);

    uartInit(UBRR);
    timer1Init();
    timer2Init();
    sei();
    adcInit();
    setupDone = true;
    
    if(setupDone){
        uartPutChar('\n');
        uartPutString("--- SETUP COMPLETE ---");
        uartPutChar('\n');
    } else {
        uartPutChar('\n');
        uartPutString("--- SETUP FAILED ---");
        isRunning = false;
        uartPutChar('\n');
    }
};

void buttonPressed() {
    ledToggle();
};

void adcInit() {
    // Set the reference voltage to AVCC.
    ADMUX |= (1 << REFS0);
    // Set the prescaler to 128.
    ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
    // Enable the ADC.
    ADCSRA |= (1 << ADEN);
};

void adcRead() {
    if(adcToggle){
        // Start the conversion.
        ADCSRA |= (1 << ADSC);
        // Wait for the conversion to complete.
        while(ADCSRA & (1 << ADSC));
        
        // Read the value.
        uint16_t value = ADC;
        int voltage = (value * 5) / 1024; // Convert the value to a 5V scale.
        uartPutString("ADC Value: ");
        uartPutInt(voltage);
        uartPutChar('\n');
    }
};

void adcEnabled() {
    adcToggle = !adcToggle;
};  