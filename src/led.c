#include <avr/io.h>
#include <stdio.h>
#include <stdbool.h>
#include "led.h"
#include "serial.h"
#include "device.h"
#include "timer.h"
#include "adc.h"

bool ledOn = false;
volatile bool ledTimer = false; 

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