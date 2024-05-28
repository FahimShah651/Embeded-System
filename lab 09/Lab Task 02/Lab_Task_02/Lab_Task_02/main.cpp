/*
 * Lab_Task_02.cpp
 *
 * Created: 6/13/2023 3:20:53 PM
 * Author : fahim
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
ISR(INT1_vect);


int main(void)
{
   DDRB = 0x08;
   TCNT0 = 0x50;
   TCCR0A = 0;
   TCCR0B = 0x05;
   TIMSK0 = 0x1;
  
	
    /* Replace with your application code */
   DDRD |=(1<<PORTD7);
   DDRD &= ~(1<<PORTD3);
   PORTD |= (1<<PORTD3);
   EICRA |= (1<<ISC11 | ISC10);
   EIMSK |= (1<<INT1);
   sei();
   
    while (1) 
    {
	   PORTB = TCNT0;
    }
	return 0;
}

ISR(INT1_vect)
{
	PORTD ^= (1<<PORTD7);
}

