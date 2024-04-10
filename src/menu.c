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

void buttonPressed() {
    ledToggle();
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
    
    // Initialize the timer
    timerInit();

    uartPutString("Setup complete.");
};

void mainMenu() {
    while(isRunning) {
        // --- DRIVER CODE ---
    bool previousButtonState = false;
    char inputString[MAX_INPUT_LENGTH];
    uartPutChar('\n');
    uartPutString("--- DEVICE ONLINE ---");
    uartPutChar('\n');
    uartPutString("Submit 'ledtoggle', 'timertoggle' or 'ledpower <0-255>' command, and press 'Enter'.");  
    uartPutChar('\n');
    while (isRunning) {
        // In order for the LED to not toggle constantly during a buttonpress, 
        // we check the current and previous state of the button.
        bool currentButtonState = !(PIND & (1 << BUTTON_PIN));
        if (currentButtonState && !previousButtonState) {
            // If button was pressed for the first time, toggle LED.
            buttonPressed();
        }
        previousButtonState = currentButtonState;
        // This condition checks the UART Receive Complete (RXC) -flag in the UART Status Register (UCSR0A),
        // and then records the userinput, as well as echoing the chars back in the Serial Monitor. Parse userinput in command.c.
        if (UCSR0A & (1 << RXC0)) {
            uartRecStringAndEcho(inputString);
            uartPutChar('\n');
            uartPutString("Received: ");
            uartPutString(inputString);
            uartPutChar('\n');
            parseUserInput(inputString);
        }
    }
    uartPutString("Program closed.");
    uartPutChar('\n');
    }

};