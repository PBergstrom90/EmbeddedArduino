#ifndef COMMAND_H
#define COMMAND_H

#define MAX_INPUT_LENGTH 20

enum Command {
    LED_TOGGLE,
    LED_POWER_VALUE,
    LED_TIMER_TOGGLE,
    ADC_TOGGLE,
    EXIT,
    INVALID_COMMAND
};

enum Command parseCommand(const char* input);
void parseUserInput(char inputString[MAX_INPUT_LENGTH]);
void executeCommand(enum Command cmd, short int value);

#endif // COMMAND_H 