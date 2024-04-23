#include <avr/io.h>
#include <stdio.h>
#include <stdbool.h>
#include "led.h"
#include "serial.h"
#include "device.h"
#include "timer.h"

bool ledOn = false;

void ledToggle() {
    ledOn = !ledOn; // Toggle LED boolean.
    setLedOn(ledOn);
};

void setLedOn(bool ledOn) {
    if(ledOn) {
        LED_ON;
    } else {
        LED_OFF;
    }
};