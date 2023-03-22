/*
-The millis() function known from Arduino
-Calling millis() will return the milliseconds since the program started
-Tested on atmega328p
-REMEMBER: Add sei(); after init_millis() to enable global interrupts!
 */

#include "millis.h"

ISR(TIMER1_COMPA_vect)
{
	timer1_millis++;
}


void init_millis(unsigned long f_cpu)
{
	unsigned long ctc_match_overflow;

	ctc_match_overflow = ((f_cpu / 1000) / 8); //when timer1 is this value, 1ms has passed

	// (Set timer to clear when matching ctc_match_overflow) | (Set clock divisor to 8)
	TCCR1B |= (1 << WGM12) | (1 << CS11); //A: wave form generation mode(ctc mode) : WGM12=1 ; clock select(prescaler=8) : CS11=1

	// high byte first, then low byte
	OCR1AH = (ctc_match_overflow >> 8);
	OCR1AL = ctc_match_overflow;

	// Enable the compare match interrupt
	TIMSK |= (1 << OCIE1A);

	//REMEMBER TO ENABLE GLOBAL INTERRUPTS AFTER THIS WITH sei(); !!!
}
unsigned long millis (void)
{
	unsigned long millis_return;

	// Ensure this cannot be disrupted
	ATOMIC_BLOCK(ATOMIC_FORCEON) {
		millis_return = timer1_millis;
	}
	return millis_return;
}



/*

void init_millis(unsigned long f_cpu)
{
	unsigned long ctc_match_overflow;

	ctc_match_overflow = ((f_cpu / 1000) / 8); //when timer0 is this value, 1ms has passed

	// (Set timer to clear when matching ctc_match_overflow) | (Set clock divisor to 8)
	TCCR0 |= (1 << WGM01) | (1 << CS01); //A: wave form generation mode(ctc mode) : WGM12=1  ; clock select(prescaler=8) : CS11=1

	// The Output Compare Register contains an 8-bit value that is continuously compared with the counter value (TCNT0).
	OCR0 = ctc_match_overflow;

	// Enable the compare match interrupt
	TIMSK |= (1 << OCIE0);

	//REMEMBER TO ENABLE GLOBAL INTERRUPTS AFTER THIS WITH sei(); !!!
}

file: main.c
Name: Timer demo
Author: Monoclecat
This demo will make the pin PORTB5 (pin 13 on the Arduino board) toggle every second

#include <avr/io.h>
#include <avr/interrupt.h>
#include <millis.h>

int main(void)
{
	DDRB = (1 << DDB5); //setting PORTB5 to an output
	PORTB ^= (1 << PORTB5);
	init_millis(16000000UL); //frequency the atmega328p is running at
	unsigned long prev_millis; //the last time the led was toggled
	prev_millis = millis();
	sei();
	for(;;)
	{
		if (millis() - prev_millis > 1000)
		{
			PORTB ^= (1 << PORTB5); //Turn on / Turn off the LED
			prev_millis = millis();
		}
	}
	return 0;
}
*/