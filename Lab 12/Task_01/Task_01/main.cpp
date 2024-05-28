/*
 * Task_01.cpp
 *
 * Created: 7/11/2023 8:35:05 AM
 * Author : fahim
 */ 

#include <avr/io.h>
#define F_CPU 16000000UL
#include <util/delay.h>

int main(void)
{
	DDRD = 0xFF;
	while (1)
	{
		PORTD = 0b00000001;
		_delay_ms(10000);
		
		PORTD = 0b00000000;
		_delay_ms(4000);
		PORTD = 0b00000010;
		_delay_ms(10000);
		
		PORTD = 0b00000011;
		_delay_ms(4000);
	}
}
