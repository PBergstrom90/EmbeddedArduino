#include <avr/io.h> 
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include "command.h"
#include "serial.h"
#include "led.h"
#include "menu.h"
#include "timer.h"
#include "device.h"

void parseUserInput(char inputString[MAX_INPUT_LENGTH]) { 
    if (strlen(inputString) > MAX_INPUT_LENGTH) {
        uartPutString("ERROR: Input length exceeds maximum allowed length.");
        uartPutChar('\n');
        return;
    }
    char command[MAX_INPUT_LENGTH];
    short int value;
    // Use sscanf to parse the input string
    if (sscanf(inputString, "%s %hd", command, &value) == 2) {
        executeCommand(parseCommand(command), value);
    } else if (sscanf(inputString, "%s", command) == 1) {
        // -1 represents no value for commands that don't require any.
        executeCommand(parseCommand(command), -1);
    } else {
        uartPutString("ERROR: Cannot parse command");
        uartPutChar('\n');
    }
};

enum Command parseCommand(const char* input) {
    if (strncmp(input, "ledtoggle", strlen("ledtoggle")) == 0) {
        return LED_TOGGLE;
    } else if (strncmp(input, "ledpower", strlen("ledpower")) == 0) {
        return LED_POWER_VALUE;
    } else if (strncmp(input, "ledtimertoggle", strlen("ledtimertoggle")) == 0) {
        return LED_TIMER_TOGGLE;
    } else if (strncmp(input, "adctoggle", strlen("adctoggle")) == 0) {
        return ADC_TOGGLE;
    } else if (strncmp(input, "adcprint", strlen("adcprint")) == 0) {
        return ADC_PRINT;
    } else if (strncmp(input, "setprescaler", strlen("setprescaler")) == 0) {
        return SET_PRESCALER;
    } else if (strncmp(input, "exit", strlen("exit")) == 0) {
        return EXIT;
    }
    return INVALID_COMMAND;
};

void executeCommand(enum Command cmd, short int value) {
    switch (cmd) {
        case LED_TOGGLE:
            ledToggle();
            uartPutString("LED is toggled.");
            uartPutChar('\n');
            break;
        case LED_POWER_VALUE:
            if(value >= MIN_POWER_VALUE && value <= MAX_POWER_VALUE) {
                ledPowerValue(value);
            } else {
                uartPutString("ERROR: Invalid LED POWERVALUE.");
                uartPutChar('\n');
            }
            break;
        case LED_TIMER_TOGGLE:
            ledTimer = !ledTimer;
            uartPutString("LED Timer is: ");
            uartPutString(ledTimer ? "Enabled." : "Disabled.");
            uartPutChar('\n');
            break;
        case ADC_TOGGLE:
            adcToggle = !adcToggle;
            uartPutString("ADC is: ");
            uartPutString(adcToggle ? "Enabled." : "Disabled.");
            uartPutChar('\n');
            break;
        case ADC_PRINT:
            adcPrintState = !adcPrintState;
            uartPutString("ADC Print is: ");
            uartPutString(adcPrintState ? "Enabled." : "Disabled.");
            uartPutChar('\n');
            break;  
        case SET_PRESCALER:
            switchPrescaler(value);
            uartPutString("Prescaler set to: ");
            uartPutInt(value);
            uartPutChar('\n');
            break;
        case EXIT:
            uartPutString("Exiting program... ");
            uartPutChar('\n');
            isRunning = false;
            break;
        case INVALID_COMMAND:
            uartPutString("ERROR: Invalid command.");
            uartPutChar('\n');
            break;
    }
};