#ifndef TIMER_H
#define TIMER_H

#include <avr/io.h>
#include <avr/interrupt.h>

extern volatile bool timer1Enabled; 
void timerInit();
ISR(TIMER1_OVF_vect);

#endif // TIMER_H
