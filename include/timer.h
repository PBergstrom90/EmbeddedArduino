#ifndef TIMER_H
#define TIMER_H

#include <avr/io.h>
#include <avr/interrupt.h>

// LED-timer values
#define MIN_TIME_MS 200
#define MAX_TIME_MS 5000

// Prescaler values
#define PRESCALER_1 1
#define PRESCALER_8 8
#define PRESCALER_64 64
#define PRESCALER_256 256
#define PRESCALER_1024 1024
#define PRESCALER_MAX_TIME_MS 4194

// Macro for determining the prescaler overflow value.
#define MAX_TIMERTICKS 65535

extern uint16_t prescalerValue;
extern volatile uint16_t overflowCount;

void timer1Init();
void timer2Init();
void adjustTimerFrequency(float frequency);
void switchPrescaler(uint16_t prescaler);

#endif // TIMER_H
