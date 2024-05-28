/*
 * Lab_08_Task_05.cpp
 *
 * Created: 6/6/2023 2:54:25 PM
 * Author : fahim
 */ 

#include <avr/io.h> // Include the AVR IO library for accessing registers and I/O operations
#define F_CPU 16000000UL // Define the frequency

void T0Delay(); // Function prototype for delay using Timer0

int main(void)
{
	DDRB = 0b00000111; // Set PORTB pins 0, 1, and 2 as output

	while (1) // Infinite loop for Square Wave 
	{
		PORTB = 0b00000111; // Set PORTB pins 0, 1, and 2 to high (  )
		T0Delay(); // Delay of ( 25% of the square wave ) using Timer0
		// Set PORTB pins 1 and 2 to high, pin 0 to low ( Pin 0 will give 25% duty cycle square wave )
		PORTB = 0b00000110; 
		T0Delay(); // Delay of ( 25% of the square wave ) using Timer0
		// Set PORTB pin 2 to high, pin 0 and pin 1 to low ( Pin 1 will give 50% duty cycle square wave )
		PORTB = 0b00000100; 
		T0Delay(); // Delay of ( 25% of the square wave ) using Timer0
		 // Set PORTB pins 1 , 2 and 0 to low ( Pin 2 will give 75% duty cycle square wave )
		PORTB = 0b00000000;
		T0Delay(); // Delay of ( 25% of the square wave ) using Timer0
		// Now one Square wave is completed
	}
}

void T0Delay()
{
	TCNT0 = 0;      // Reset Timer0 counter
	TCCR0B = 0x01;  // Start Timer0 normal mode
	while ((TIFR0 & (1 << TOV0)) == 0); // Wait for Timer0 overflow flag to be set
	TCCR0A = 0;   // Reset Timer0 control register A
	TIFR0 = 0x01; // Clear Timer0 overflow flag
}
