#include "avr/io.h"
#include "delay.h"
int main()
{
	DDRB = 0xFF;
	while(1)
	{
		PORTB = 1;
		
		PORTB = 1;
		
	}
	
	
	return 0;
}