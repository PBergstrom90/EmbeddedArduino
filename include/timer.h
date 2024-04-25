#ifndef TIMER_H
#define TIMER_H

#include <avr/io.h>
#include <avr/interrupt.h>

extern volatile bool timer1Enabled; 
void timer1Init();

#endif // TIMER_H
