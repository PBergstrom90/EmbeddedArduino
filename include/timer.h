#ifndef TIMER_H
#define TIMER_H

#include <avr/io.h>
#include <avr/interrupt.h>

// LED-timer values
#define MIN_TIME_MS 500
#define MAX_TIME_MS 10000

void timer2Init();
void delayMs(uint16_t ms);

#endif // TIMER_H
