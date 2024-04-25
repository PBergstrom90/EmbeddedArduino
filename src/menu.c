#include <stdio.h>
#include <stdbool.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include "menu.h"
#include "timer.h"
#include "serial.h"
#include "command.h"
#include "led.h"

bool isRunning = true;

void onButtonPressed() {
    ledToggle();
};

bool isButtonPressed() {
    return !(BUTTON_PIN_REGISTER & (1 << BUTTON_PIN));
};

void setup() {
    // Set LED pin as output.
    DDRD |= (1 << LED_PIN);
    // Set Button pin as input.
    DDRD &= ~(1 << BUTTON_PIN);
    // Enable pull-up resistor for Button pin. 
    // Because there is a 10k-Ohm resistor between 5V and the button.
    PORTD |= (1 << BUTTON_PIN);
    uartInit(UBRR);
    timer1Init();
    uartPutString("Setup complete.");
};

void mainMenu() {
    bool previousButtonState = false;
    uartPutChar('\n');
    uartPutString("--- DEVICE ONLINE ---");
    uartPutChar('\n');
    uartPutString("Submit 'ledtoggle' or 'timertoggle' command, and press 'Enter'.");  
    uartPutChar('\n');
    // DRIVER CODE
    while (isRunning) {
        // In order for the LED to not toggle constantly during a buttonpress, 
        // we check the current and previous state of the button.
        bool buttonPressed = isButtonPressed();
        if (buttonPressed && !previousButtonState) {
            onButtonPressed();
        }
        previousButtonState = buttonPressed;

        uartLoop();
    }
};