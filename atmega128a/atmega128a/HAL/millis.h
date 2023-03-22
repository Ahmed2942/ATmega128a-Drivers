#ifndef MILLIS_H_
#define MILLIS_H_

#include <avr/io.h>
#include <util/atomic.h>
#include <avr/interrupt.h>

volatile unsigned long timer1_millis;
//NOTE: A unsigned long holds values from 0 to 4,294,967,295 (2^32 - 1).
//Then it will roll over to 0 after reaching its maximum value.

ISR(TIMER0_COMP_vect);
void init_millis(unsigned long f_cpu);
unsigned long millis (void);

#endif /* MILLIS_H_ */