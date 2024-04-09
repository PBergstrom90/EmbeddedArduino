#include <stdio.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include "command.h"
#include "timer.h"
#include "menu.h"
#include "led.h"
#include "serial.h"

int main() {
    
    setup();
    mainMenu();
    
    return 0;
}