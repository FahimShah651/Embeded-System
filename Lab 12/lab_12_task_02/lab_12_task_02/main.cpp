#define F_CPU 800000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <string.h>
#include <stdlib.h>
#define Trigger_pin PB1
#define LCD_Port PORTD
#define LCD_DPin DDRD
#define RSPIN PD0
#define ENPIN PD1

int TimerOverflow = 0;

ISR(TIMER1_OVF_vect)
{
	TimerOverflow++;
}

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

int main(void)
{
	char string[10];
	long count;
	double distance;
	
	DDRB |= (1<<PORTB1);
	DDRB |= ~(1<<PORTB0);
	PORTB |= (1<<PORTB0);
	
	LCD_Init();
	LCD_Printpos(0, 0, "Ultrasonic");
	
	sei();
	TIMSK1 = ((1 << TOIE1));
	TCCR1A = 0;
	while (1)
	{
		PORTB |= (1 << Trigger_pin);
		_delay_us(12);
		PORTB &= (~(1 << Trigger_pin));
		
		TCNT1 = 0;
		TCCR1B = 0x41;
		TIFR1 = 1<<ICF1;
		TIFR1 = 1<<TOV1;
		
		while ((TIFR1 & (1 << ICF1)) == 0);
		TCNT1 = 0;
		TCCR1B = 0x01;
		TIFR1 = 1<<ICF1;
		TIFR1 = 1<<TOV1;
		TimerOverflow = 0;
		
		while ((TIFR1 & (1 << ICF1)) == 0);
		count = ICR1 + (65535 * TimerOverflow);
		distance = (double)count / 466.47;
		
		dtostrf(distance, 2, 2, string);
		strcat(string, " cm   ");
		LCD_Printpos(1, 0, "Dist = ");
		LCD_Printpos(1, 7, string);
		_delay_ms(500);
		
	}
}