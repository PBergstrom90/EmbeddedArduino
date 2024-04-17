#include <stdio.h>
#include <stdbool.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include "command.h"
#include "timer.h"
#include "menu.h"
#include "led.h"
#include "serial.h"
#include "device.h"
#include "adc.h"

int main() {

    setup();
    mainMenu();

    uartPutString("--- DEVICE OFFLINE ---");
    uartPutChar('\n');
    
    return 0;
}