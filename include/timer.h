#ifndef TIMER_H
#define TIMER_H

#include <avr/io.h>
#include <avr/interrupt.h>

// Timer values
#define BUTTON_COUNTER TCNT1

// Macro for determining the prescaler overflow value.
#define MAX_TIMERTICKS 65535

extern volatile uint16_t overflowCount;

void timer0Init();
void timer1Init();

#endif // TIMER_H
