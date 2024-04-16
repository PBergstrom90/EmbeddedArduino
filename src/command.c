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
    if (strlen(inputString) > MAX_INPUT_LENGTH) {
        uartPutString("ERROR: Input exceeds maximum allowed length.");
        uartPutChar('\n');
        return;
    }
    char command[MAX_INPUT_LENGTH];
    short int value;
    short int timeMs;
    // Use sscanf to parse the input string
    if (sscanf(inputString, "%s %hd %hd", command, &value, &timeMs) == 3) {
        executeCommand(parseCommand(command), value, timeMs);
    } else if (sscanf(inputString, "%s %hd", command, &value) == 2) {
        executeCommand(parseCommand(command), value, -1);
    } else if (sscanf(inputString, "%s", command) == 1) {
        executeCommand(parseCommand(command), -1, -1);
    } else {
        uartPutString("ERROR: Cannot parse command");
        uartPutChar('\n');
    }
};

enum Command parseCommand(const char* input) {
    if (strncmp(input, "ledtoggle", strlen("ledtoggle")) == 0) {
        return LED_TOGGLE_CMD;
    } else if (strncmp(input, "ledpower", strlen("ledpower")) == 0) {
        return LED_POWER_VALUE_CMD;
    } else if (strncmp(input, "ledtimertoggle", strlen("ledtimertoggle")) == 0) {
        return LED_TIMER_TOGGLE_CMD;
    } else if (strncmp(input, "ledbrightness", strlen("ledbrightness")) == 0) {
        return LED_BRIGHTNESS_CMD;
    } else if (strncmp(input, "adctoggle", strlen("adctoggle")) == 0) {
        return ADC_TOGGLE_CMD;
    } else if (strncmp(input, "exit", strlen("exit")) == 0) {
        return EXIT_CMD;
    }
    return INVALID_CMD;
};

void executeCommand(enum Command cmd, short int value, short int timeMs) {
    switch (cmd) {
        case LED_TOGGLE_CMD:
            ledToggle();
            uartPutString("LED is toggled.");
            uartPutChar('\n');
            break;
        case LED_POWER_VALUE_CMD:
            if(value >= MIN_POWER_VALUE && value <= MAX_POWER_VALUE && timeMs >= MIN_TIME_MS && timeMs <= MAX_TIME_MS) {
                ledPowerValue(value, timeMs);
            } else {
                uartPutString("ERROR: Invalid LED POWERVALUE or timeMs.");
                uartPutChar('\n');
            }
            break;
        case LED_TIMER_TOGGLE_CMD:
            ledTimer = !ledTimer;
            uartPutString("LED Timer is: ");
            uartPutString(ledTimer ? "Enabled." : "Disabled.");
            uartPutChar('\n');
            break;
        case LED_BRIGHTNESS_CMD:
            if(value >= MIN_POWER_VALUE && value <= MAX_POWER_VALUE) {
                currentDutyCycle = value;
                uartPutString("LED brightness is set to: ");
                uartPutChar(value);
                uartPutChar('\n');
            } else {
                uartPutString("ERROR: Invalid LED BRIGHTNESS value.");
                uartPutChar('\n');
            }
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