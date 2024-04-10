#ifndef TIMER_H
#define TIMER_H

#include <avr/io.h>
#include <avr/interrupt.h>

extern volatile bool timer1Enabled;
extern volatile bool timer2Enabled;
void timer1Init();
void timer2Init();

#endif // TIMER_H
