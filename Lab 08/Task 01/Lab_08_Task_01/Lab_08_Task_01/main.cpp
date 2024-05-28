/*
 * Lab_08_Task_01.cpp
 *
 * Created: 6/6/2023 1:24:24 PM
 * Author : fahim
 */ 

#include <avr/io.h>
#define F_CPU 16000000UL
#include <util/delay.h>

int main(void)
{
   DDRB = 0x01;
   
   while(1)
   {
	   PORTB= 0x01;
	   _delay_ms(500);
	   PORTB = 0;
	   _delay_ms(500);
   }
}

