#ifndef TIMER_H
#define TIMER_H

#include <avr/io.h>
#include <avr/interrupt.h>

#define MIN_TIME_MS 200
#define MAX_TIME_MS 5000

void timer1Init();
void timer2Init();
void switchTimerValue(uint32_t timerValue);
void adjustTimerFrequency(float frequency);
void switchPrescaler(uint16_t prescaler);

#endif // TIMER_H
