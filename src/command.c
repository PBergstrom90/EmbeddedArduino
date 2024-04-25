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

void parseUserInput(const char *inputString) { 
    if (strlen(inputString) > RX_BUF_SIZE) {
        uartPutString("ERROR: Input length exceeds maximum allowed length.");
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

enum Command parseCommand(const char *input) {
    if (strncmp(input, "ledtoggle", strlen("ledtoggle")) == 0) {
        return LED_TOGGLE_CMD;
    } else if (strncmp(input, "timertoggle", strlen("timertoggle")) == 0) {
        return TIMER_TOGGLE_CMD;
    }else if (strcmp(input, "exit") == 0) {
        return EXIT_CMD;
    }
    return INVALID_CMD;
};

void executeCommand(enum Command cmd, short value) {
    switch (cmd) {
        case LED_TOGGLE_CMD:
                ledToggle();
                uartPutString("LED is toggled.");
                uartPutChar('\n');
            break;
        case TIMER_TOGGLE_CMD:
            timer1Enabled = !timer1Enabled;
            uartPutString("Timer 1 is: ");
            uartPutString(timer1Enabled ? "Enabled." : "Disabled.");
            uartPutChar('\n');
            break;
        case EXIT_CMD:
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