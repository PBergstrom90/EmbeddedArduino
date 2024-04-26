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
#include "adc.h"

void parseUserInput(const char *inputString) { 
    if (strlen(inputString) > RX_BUF_SIZE) {
        uartPutString("ERROR: Input exceeds maximum allowed length.");
        uartPutChar('\n');
        return;
    }
    char command[RX_BUF_SIZE];
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
        return LED_TOGGLE_CMD;
    } else if (strncmp(input, "ledtimertoggle", strlen("ledtimertoggle")) == 0) {
        return LED_TIMER_TOGGLE_CMD;
    } else if (strncmp(input, "adctoggle", strlen("adctoggle")) == 0) {
        return ADC_TOGGLE_CMD;
    } else if (strncmp(input, "exit", strlen("exit")) == 0) {
        return EXIT_CMD;
    }
    return INVALID_CMD;
};

void executeCommand(enum Command cmd, short int value) {
    switch (cmd) {
        case LED_TOGGLE_CMD:
            ledToggle();
            uartPutString("LED is toggled.");
            uartPutChar('\n');
            break;
        case LED_TIMER_TOGGLE_CMD:
            ledTimer = !ledTimer;
            uartPutString("LED Timer is: ");
            uartPutString(ledTimer ? "Enabled." : "Disabled.");
            uartPutChar('\n');
            break;
        case ADC_TOGGLE_CMD:
            adcToggle = !adcToggle;
            uartPutString("ADC is: ");
            uartPutString(adcToggle ? "Enabled." : "Disabled.");
            uartPutChar('\n');
            break;
        case EXIT_CMD:
            uartPutChar('\n');
            uartPutString("Exiting program... ");
            uartPutChar('\n');
            isRunning = false;
            break;
        case INVALID_CMD:
            uartPutString("ERROR: Invalid command.");
            uartPutChar('\n');
            break;
    }
};