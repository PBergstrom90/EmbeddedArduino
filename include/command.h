#ifndef COMMAND_H
#define COMMAND_H

enum Command {
    LED_TOGGLE_CMD,
    TIMER_TOGGLE_CMD,
    EXIT_CMD,
    INVALID_CMD
};

enum Command parseCommand(const char *input);
void parseUserInput(const char *inputString);
void executeCommand(enum Command cmd, short int value);

#endif // COMMAND_H 