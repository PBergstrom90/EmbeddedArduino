#include <stdio.h>
#include <stdbool.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h> 
#include "device.h"
#include "led.h"
#include "command.h"
#include "serial.h"
#include "timer.h"
#include "menu.h"

volatile bool adcToggle = false;
volatile bool adcReadState = false;
volatile bool adcPrintState = false;

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
    sei();
    adcInit();
    adcConvert();
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

// Convert the potentiometer value to adjust the timervalue for Timer 1.
void adcRead() {
    // Read the ADC value.
    uint16_t adcValue = ADC;
    float millivolts = ((float)adcValue / 1023) * 5000;
    uint32_t timerValue;
    if (millivolts < 100) {
        timerValue = 15649;
    } else if(millivolts < 1000) {
        timerValue = 15624; // 1 second.
    } else if (millivolts < 2000) {
        timerValue = 12499; // 800ms.
    } else if (millivolts < 3000) {
        timerValue = 7812; // 500 ms
    } else if (millivolts < 4000) {
        timerValue = 3124; // 200 ms.
    } else {
        timerValue = 1562; // 100 ms.
    }
    
    switchTimerValue(timerValue);
    
    if(adcPrintState){ // If the overflowtimer has been triggered, print the adc value.
        adcPrint(timerValue, millivolts);
        adcPrintState = false;
    }
    
    adcConvert(); // Start the next conversion.
};

void adcPrint(uint32_t timerValue, float millivolts) {
    uartPutString("Timervalue set to: ");
    uartPutInt(timerValue);
    uartPutChar('\n');
    uartPutString("ADC Value: ");
    uartPutInt((uint16_t)millivolts);
    uartPutString(" millivolts.");
    uartPutChar('\n');
};

void adcConvert() {
    // Start the ADC-Conversion.
    ADCSRA |= (1 << ADSC);
};