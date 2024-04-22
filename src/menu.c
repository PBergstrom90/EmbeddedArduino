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
#include "adc.h"

bool isRunning = true;

void mainMenu() {
    bool previousButtonState = false;
    uartPutString("--- DEVICE ONLINE ---");
    uartPutChar('\n');
    uartPutString("Submit 'ledtoggle', 'ledtimertoggle', 'ledbrightness <0-255>', 'ledpower <0-255> <200-5000>' or 'buttoncounter' command, and press 'Enter'.");  
    uartPutChar('\n');
    while (isRunning) {
        // In order for the LED to not toggle constantly during a buttonpress, 
        // we check the current and previous state of the button.
        bool buttonPressed = isButtonPressed();
        if (buttonPressed && !previousButtonState) {
            onButtonPressed();
        }
        previousButtonState = buttonPressed;

        if(buttonPrint){
            buttonCounterPrint();
            buttonPrint = false;
        }

        uartLoop();
    }
};