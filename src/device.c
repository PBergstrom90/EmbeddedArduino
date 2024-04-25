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
        LED_ON;
    } else {
        LED_OFF;
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
 
// This following solution is not perfect, since it is using the inbuilt "_delay_ms" function and therefore is blocking the rest of the program.
// But I have connected a 10uF capacitor to the button, wich makes the bounce noise less significant.
// The delay is set to 75 ms, since anything shorter should be within the bounce time, according to this calculator: https://protological.com/debounce-calaculator/
// This solution is good enough for this project.
enum ButtonState buttonDebounce(enum ButtonState btnState) {
    bool currentButtonState = isButtonPressed();
    switch (btnState) {
        case BUTTON_RELEASED:
            if (currentButtonState) {
                btnState = BUTTON_DEBOUNCING;
            }
            break;
        case BUTTON_PRESSED:
            if (!currentButtonState) {
                btnState = BUTTON_DEBOUNCING;
            }
            break;
        case BUTTON_DEBOUNCING:
            _delay_ms(DEBOUNCE_DELAY);
            // Check if the button state is stable after the delay
            if (currentButtonState == isButtonPressed()) {
                // If the button is pressed after the delay, update the state
                if (currentButtonState) {
                    btnState = BUTTON_PRESSED;
                } 
                // If the button is released after the delay, update the state
                else {
                    btnState = BUTTON_RELEASED;
                }
            }
            break;
    }
    return btnState;
}