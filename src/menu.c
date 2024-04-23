#include <stdio.h>
#include <stdbool.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include "menu.h"
#include "timer.h"
#include "serial.h"
#include "command.h"
#include "led.h"
#include "device.h"

bool isRunning = true;

void mainMenu() {
    uartPutString("--- DEVICE ONLINE ---");
    uartPutChar('\n');
    uartPutString("Submit 'ledtoggle' or 'buttoncounter' command, and press 'Enter'.");  
    uartPutChar('\n');
    enum ButtonState buttonState = BUTTON_RELEASED;
    bool previousButtonState = false;
    // DRIVER CODE
    while (isRunning) {
        buttonState = buttonDebounce(buttonState);
        if (buttonState == BUTTON_PRESSED && !previousButtonState) {
            onButtonPressed();
        }
        previousButtonState = (buttonState == BUTTON_PRESSED);
        
        // Print the buttoncounter value every second, with Timer0.
        if(buttonPrint){
            buttonCounterPrint();
            buttonPrint = false;
        }

        uartLoop();
    }
};