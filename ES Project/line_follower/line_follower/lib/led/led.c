/*
 * led.c
 *
 * Created: 5/29/2012 5:45:23 PM
 *  Author: Avinash Gupta
 */ 
#include <avr/io.h>

void LEDInit()
{
	//Make i/o pins as output type
	DDRD|=(0Xf0);
	DDRB|=(1<<PB0);
	
	//Make them high to turn off led.
	PORTD|=(0Xf0);
	PORTB|=(1<<PB0);
}

void LEDOff(uint8_t id)
{
	if(id>5) return;
	
	id=6-id;
	
	if(id==1)
	{
		PORTB|=(1<<PB0);
	}
	else if(id<=5)
	{
		PORTD|=(1<<(2+id));
	}
}

void LEDOn(uint8_t id)
{
	if(id>5) return;
	
	id=6-id;
	
	if(id==1)
	{
		PORTB&=~(1<<PB0);
	}
	else if(id<=5)
	{
		PORTD&=~(1<<(2+id));
	}
}