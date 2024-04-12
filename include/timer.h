#ifndef TIMER_H
#define TIMER_H

#include <avr/io.h>
#include <avr/interrupt.h>

void timer1Init();
void switchTimerValue(uint32_t timerValue);
void switchPrescaler(uint16_t prescaler);

#endif // TIMER_H
