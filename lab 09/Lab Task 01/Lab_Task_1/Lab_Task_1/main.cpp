/*
 * Lab_Task_1.cpp
 *
 * Created: 6/13/2023 1:24:37 PM
 * Author : fahim
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#define F_CPU 16000000UL


int main(void)
{
    DDRB |=0x20;
	
	OCR0A = 0x35;	TCNT0 = 0;	TCCR0A = 0x02;	TCCR0B = 0x05;
	TIMSK0 = 0x02;
	sei();
	
	DDRC = 0x0;
	DDRD =  0xFF;
	
	while(1)
	{
		PORTD = PINC;
	}
}


	ISR (TIMER0_COMPA_vect)
	{	   TCNT0 = 0;
	   PORTB ^=0x20;
	}

