/*
 * adc.c
 *
 * Created: 2/25/2012 9:18:03 AM
 *  Author: Avinash Gupta
 */
#include <avr/io.h>
#include "adc.h"

//Function To Initialize the ADC Module
void InitADC()
{
   ADMUX=(1<<REFS0);                                  	// For Aref=AVcc;
   ADCSRA=(1<<ADEN)|(1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0);    //Rrescalar div factor =128

}

/* 

Function To Read ADC Channel

Argument: Channel Number between 0-7
Return Value : Between 0-1023

*/
uint16_t ReadADC(uint8_t ch)
{
   //Select ADC Channel ch must be 0-7
   ch=ch&0b00000111;  
   ADMUX&=0b11100000;
   ADMUX|=ch;

   //Start Single conversion
   ADCSRA|=(1<<ADSC);

   //Wait for conversion to complete
   while(!(ADCSRA & (1<<ADIF)));

   //Clear ADIF by writing one to it

   //Note you may be wondering why we have write one to clear it
   //This is standard way of clearing bits in io as said in datasheets.
   //The code writes '1' but it result in setting bit to '0' !!!

   ADCSRA|=(1<<ADIF);

   return(ADC);
} 
