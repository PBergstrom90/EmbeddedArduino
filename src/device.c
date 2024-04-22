#include <stdio.h>
#include <stdbool.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h> 
#include "device.h"
#include "adc.h"
#include "led.h"
#include "command.h"
#include "serial.h"
#include "timer.h"
#include "menu.h"

int buttonCounter = 0;
bool buttonPrint = false;
bool buttonTimer = false;

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
    timer0Init();
    timer1Init();
    timer2Init();
    sei(); // Enable global interrupts.
    setupDone = true; // Setup is complete.
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

void onButtonPressed() {
    ledOn = !ledOn; // Toggle LED boolean.
    if(ledOn) {
        setLedBrightness(MAX_POWER_VALUE);
    } else {
        setLedBrightness(MIN_POWER_VALUE);
    }
};

bool isButtonPressed() {
    return !(BUTTON_PIN_REGISTER & (1 << BUTTON_PIN));
};

void buttonCounterPrint() {
    uartPutString("Buttoncounter: ");
    uartPutInt(BUTTON_COUNTER);
    uartPutChar('\n');
};