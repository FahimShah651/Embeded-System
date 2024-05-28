/*
 * Lab_08_Task_03.cpp
 *
 * Created: 6/6/2023 1:46:23 PM
 * Author : fahim
 */ 

#include <avr/io.h> // Include the AVR IO library for accessing registers and I/O operations
#define F_CPU 16000000UL // Define the CPU frequency for delay functions

int main(void)
{
	DDRB = 0b00000010; // Set the direction of PORTB pin 1 as output (pin 0 is input by default)
	DDRC = 0x00; // Set the direction of PORTC as input (all pins of PORTC are inputs)

	while(1) // Infinite loop to continuously monitor the input pin
	{
		if(PINC & 0b00000001) // If the least significant bit of PINC is high (input pin is high)
		{
			PORTB = 0x00; // Set PORTB pin 1 to low (turn off the LED)
		}
		else
		{
			PORTB = 0b00000010; // Set PORTB pin 1 to high (turn on the LED)
		}
	}
	
	return 0;
}
