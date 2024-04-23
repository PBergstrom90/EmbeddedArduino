#ifndef COMMAND_H
#define COMMAND_H

enum Command {
    LED_TOGGLE_CMD,
    BUTTON_COUNTER_CMD,
    EXIT_CMD,
    INVALID_CMD
};

enum Command parseCommand(const char* input);
void parseUserInput(const char *inputString);
void executeCommand(enum Command cmd, short int value, short int timeMs);

#endif // COMMAND_H 