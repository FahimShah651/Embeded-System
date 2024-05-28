/*
 * Lab_08_ask_04.cpp
 *
 * Created: 6/6/2023 2:30:27 PM
 * Author : fahim
 */ 

#include <avr/io.h>
#define F_CPU 16000000L
void T0Delay();

int main(void)
{
   DDRD = 0x022;
    while (1) 
    {
		T0Delay();
		PORTD =PORTD ^ 0x02;
    }
}

void T0Delay()
{
	TCNT0 =0;
	TCCR0B = 0x01;
	while ((TIFR0&(1<<TOV0)) == 0);
	TCCR0A = 0;
	TIFR0 = 0x01;
	
}

