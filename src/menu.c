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
    uartPutString("Submit 'ledtoggle' or 'ledramptime <500-10000>' command, and press 'Enter'.");  
    uartPutChar('\n');
    // DRIVER CODE
    while (isRunning) {
        uartLoop();
    }
};