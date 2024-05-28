/*
 * Lab_11.cpp
 *
 * Created: 7/4/2023 1:25:58 PM
 * Author : fahim
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#define LCD_Port PORTD
#define LCD_DPin  DDRD
#define RSPIN PD0
#define ENPIN PD1

void LCD_Action(unsigned char cmnd)
{
	LCD_Port = (LCD_Port & 0x0F) | (cmnd & 0xF0);
	LCD_Port &= ~ (1<<RSPIN);
	LCD_Port |= (1<<ENPIN);
	_delay_us(1);
	LCD_Port &= ~ (1<<ENPIN);
	_delay_us(200);
	LCD_Port = (LCD_Port & 0x0F) | (cmnd << 4);
	LCD_Port |= (1<<ENPIN);
	_delay_us(1);
	LCD_Port &= ~ (1<<ENPIN);
	_delay_ms(2);
}

void LCD_Init (void)
{
	LCD_DPin = 0xFF;
	_delay_ms(15);
	LCD_Action(0x33);
	LCD_Action(0x32);
	LCD_Action(0x28);
	LCD_Action(0x02);
	LCD_Action(0x0c);
	LCD_Action(0x06);
	LCD_Action(0x01);
	_delay_ms(2);
}

void LCD_Clear()
{
	LCD_Action (0x01);
	_delay_ms(2);
	LCD_Action (0x80);
}

void LCD_Print (char *str)
{
	int i;
	for(i=0; str[i]!=0; i++)
	{
		LCD_Port = (LCD_Port & 0x0F) | (str[i] & 0xF0);
		LCD_Port |= (1<<RSPIN);
		LCD_Port|= (1<<ENPIN);
		_delay_us(1);
		LCD_Port &= ~ (1<<ENPIN);
		_delay_us(200);
		LCD_Port = (LCD_Port & 0x0F) | (str[i] << 4);
		LCD_Port |= (1<<ENPIN);
		_delay_us(1);
		LCD_Port &= ~ (1<<ENPIN);
		_delay_ms(2);
	}
}

void LCD_Printpos (char row, char pos, char *str)
{
	if (row == 0 && pos<16)
	LCD_Action((pos & 0x0F)|0x80);
	else if (row == 1 && pos<16)
	LCD_Action((pos & 0x0F)|0xC0);
	LCD_Print(str);
}

void servo1 ()
{
	TCCR1A |=(1<<WGM11)|(1<<COM1A1);
	TCCR1B |= (1<<WGM12)|(1<<WGM13)|(1<<CS11);
	ICR1 = 39999;
	int offset = 800;
	{
		OCR1A = 1999+ offset;
		_delay_ms(500);
	}
}

void servo2 ()
{
	TCCR1A |=(1<<WGM11)|(1<<COM1A1);
	TCCR1B |= (1<<WGM12)|(1<<WGM13)|(1<<CS11);
	ICR1 = 39999;
	int offset = 800;
	{
		OCR1A = 999 - offset;
		_delay_ms(500);
	}
}

int main(void)
{
	LCD_Init();
	unsigned char z;
	DDRC = 0;
	
	while (1)
	{
		z = PINC;
		z = z & 0b00000011;
		
		switch(z)
		{
			case(0):
			{
				LCD_Printpos(0,0,"Waziristan");
				LCD_Printpos(1,0,"Checkpost");
				_delay_ms(1000);
				LCD_Clear();
				break;
			}
			case (1):
			{
				LCD_Clear();
				LCD_Printpos(0,0,"Your Identity");
				LCD_Printpos(1,0,"is Cleared");
				DDRB |= 1<<PINB1;
				servo1();
				_delay_ms(1000);
				break;
			}
			case (2):
			{
				LCD_Clear();
				LCD_Printpos(0,0,"Thanks for");
				LCD_Printpos(1,0,"your cooperation");
				DDRB |= 1<<PINB1;
				servo2();
				_delay_ms(1000);
				break;
			}
			case (3):
			{
				LCD_Clear();
				LCD_Printpos(0,0,"Enjoy your");
				LCD_Printpos(1,0,"Trip");
				_delay_ms(1000);
				break;
			}
		}
		
	}
	return 0;
}
