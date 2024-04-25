#include <avr/io.h>
#include <stdio.h>
#include <stdbool.h>
#include "led.h"
#include "serial.h"

bool ledOn = false;

void ledToggle() {
    LED_TOGGLE;
};

void setLedOn(bool ledOn) {
    if(ledOn) {
        LED_ON;
    } else {
        LED_OFF;
    }
};