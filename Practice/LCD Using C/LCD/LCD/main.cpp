/*
 * LCD.cpp
 *
 * Created: 6/21/2023 11:44:49 AM
 * Author : fahim
 */ 
#define  F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#define  DL _delay_ms(10);

void lcd_init();
void lcd_data(char data);
void lcd_cmd(char cmd);
void lcd_string(char *str);

void lcd_init()
{
	DDRD = 0xff;
	DDRB |= (1<<0)|(1<<1)|(1<<2);
	lcd_cmd(0x38);
	lcd_cmd(0x01);
	lcd_cmd(0x0e);
	lcd_cmd(0x80);
}

void lcd_cmd(char cmd)
{
	PORTD = cmd;
	PORTB |=(1<<2);
	PORTB &=~((1<<0)|(1<<1));
	DL;
	PORTB  &=~(1<<2);
	DL;
}

void lcd_data(char data)
{
	PORTD =data;
	PORTB |= (1<<0)|(1<<2);
	PORTB &=~(1<<1);
	DL;
	PORTB &=~(1<<2);
	DL;
}

void lcd_string(char *str)
{
	while(*str != '\0')
	{
	lcd_data(*str);
	str++;	
	}
}




int main()
{
	lcd_init();
	lcd_cmd(0x80);
	lcd_string("Fahim Shah , is the student of NAMAL");
	DL;
	
   return 0;
}

