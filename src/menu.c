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
    bool previousButtonState = false;
    uartPutString("--- DEVICE ONLINE ---");
    uartPutChar('\n');
    uartPutString("Submit 'ledtoggle' or 'ledramptime <200-4000>' command, and press 'Enter'.");  
    uartPutChar('\n');
    while (isRunning) {
        bool buttonPressed = isButtonPressed();
        if (buttonPressed && !previousButtonState) {
            onButtonPressed();
        }
        previousButtonState = buttonPressed;

        uartLoop();
    }
};