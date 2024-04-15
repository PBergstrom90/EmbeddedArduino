#include <stdio.h>
#include <stdbool.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h> 
#include "adc.h"
#include "device.h"
#include "led.h"
#include "command.h"
#include "serial.h"
#include "timer.h"
#include "menu.h"

volatile bool adcToggle = false;
volatile bool adcReadState = false;
volatile bool adcPrintState = false;

void adcLoop(){
    // If the ADC is toggled, convert the ADC value.
    if(adcToggle){
        adcConvert();
        if(adcReadState){
            float millivolts = adcRead();
            if(adcPrintState){ // If the print-timer has been triggered, print the ADC value. 
                adcPrint(millivolts);
                adcPrintState = false;
            }
        }
    }
};

void adcInit() {
    // Set the reference voltage to AVCC.
    ADMUX |= (1 << REFS0);
    // Set the prescaler to 128.
    ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
    // Freerunning mode
    ADCSRB = 0;
    // Enable the ADC.
    ADCSRA |= (1 << ADEN);
    // Enable the ADC interrupt.
    ADCSRA |= (1 << ADIE);
};

// Convert the potentiometer value to adjust the timervalue for Timer 1.
float adcRead() {
    // Read the ADC value.
    uint16_t adcValue = ADC;
    float millivolts = ((float)adcValue / 1023) * 5000;
    uint32_t timerValue;
    if (millivolts < 100) {
        setLedOn(true);
    } else if(millivolts < 1000) {
        timerValue = 15624; // 1 second.
    } else if (millivolts < 2000) {
        timerValue = 12499; // 800ms.
    } else if (millivolts < 3000) {
        timerValue = 7812; // 500 ms
    } else if (millivolts < 4000) {
        timerValue = 3124; // 200 ms.
    } else if (millivolts < 5000){
        timerValue = 1562; // 100 ms.
    }
    switchTimerValue(timerValue);
    return millivolts;
};

void adcPrint(float millivolts) {
    uartPutString("ADC Value: ");
    uartPutInt((uint16_t)millivolts);
    uartPutString(" millivolts.");
    uartPutChar('\n');
};

void adcConvert() {
    // Start the ADC-Conversion.
    ADCSRA |= (1 << ADSC);
};