#ifndef COMMAND_H
#define COMMAND_H

#define MAX_INPUT_LENGTH 25

enum Command {
    LED_TOGGLE,
    LED_POWER_VALUE,
    LED_TIMER_TOGGLE,
    ADC_TOGGLE,
    ADC_PRINT,
    SET_PRESCALER,
    EXIT,
    INVALID_COMMAND
};

enum Command parseCommand(const char* input);
void parseUserInput(const char *inputString);
void executeCommand(enum Command cmd, short int value);

#endif // COMMAND_H 