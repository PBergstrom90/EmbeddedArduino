#ifndef TIMER_H
#define TIMER_H

#include <avr/io.h>
#include <avr/interrupt.h>

// Timer values
#define BUTTON_COUNTER TCNT1

void timer1Init();
void timer2Init();

#endif // TIMER_H
