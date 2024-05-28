/*
 * lab_10.cpp
 *
 * Created: 6/20/2023 1:18:42 PM
 * Author : fahim
 */ 

#define F_CPU 16000000UL  // AVR frequency
#include <avr/io.h>       // AVR standard I/O header
#include <util/delay.h>   // Delay header
#include <inttypes.h>     // Integer types header
#define LCD_Port PORTD    // LCD data port
#define LCD_DPin  DDRD    // LCD data direction register
#define RSPIN PD0         // Register select pin for LCD
#define ENPIN PD1         // Enable pin for LCD

// Function to send a command to the LCD
void LCD_Action(unsigned char cmnd)
{
	LCD_Port = (LCD_Port & 0x0F) | (cmnd & 0xF0); // Send high nibble of command
	LCD_Port &= ~(1 << RSPIN);      // RS = 0 for command mode
	LCD_Port |= (1 << ENPIN);        // Enable LCD (EN = 1) for high-to-low transition
	_delay_us(1);                    // Wait for enable pulse width
	LCD_Port &= ~(1 << ENPIN);      // Disable LCD (EN = 0) for low-to-high transition
	_delay_us(200);                  // Wait for command execution time
	LCD_Port = (LCD_Port & 0x0F) | (cmnd << 4);  // Send low nibble of command
	LCD_Port |= (1 << ENPIN);        // Enable LCD (EN = 1) for high-to-low transition
	_delay_us(1);                    // Wait for enable pulse width
	LCD_Port &= ~(1 << ENPIN);      // Disable LCD (EN = 0) for low-to-high transition
	_delay_ms(2);                    // Wait for command execution time
}

// Function to initialize the LCD
void LCD_Init (void)
{
	LCD_DPin = 0xFF;      // Set LCD data pins as output
	_delay_ms(15);        // Power-up delay
	
	LCD_Action(0x33);    // Initialization sequence for 4bit data 
	LCD_Action(0x32);    // Initialization sequence for 4bit data
	LCD_Action(0x28);    // 2 lines and 5x7 matrix (4-bit mode)
	LCD_Action(0x02);    // Return home
	LCD_Action(0x0C);    // Display on, cursor off
	LCD_Action(0x06);    // Shift cursor right
	LCD_Action(0x01);    // Clear display
	_delay_ms(2);        // Wait for initialization to complete
}

// Function to clear the LCD display
void LCD_Clear()
{
	LCD_Action(0x01);  // Clear display
	_delay_ms(2);      // Wait for clear operation to complete
	LCD_Action(0x80);  // Move cursor to the beginning of the first line
}

// Function to print a string on the LCD
void LCD_Print (char *str)
{
	int i;  // Index variable
	for(i=0; str[i]!=0; i++)  // Iterate through each character in the string
	{
		LCD_Port = (LCD_Port & 0x0F) | (str[i] & 0xF0);  // Send high nibble of character
		LCD_Port |= (1<<RSPIN);                         // Set RS pin high for data mode
		LCD_Port|= (1<<ENPIN);                          // Enable LCD (EN = 1) for high-to-low transition
		_delay_us(1);                                   // Wait for enable pulse width
		LCD_Port &= ~(1<<ENPIN);                         // Disable LCD (EN = 0) for low-to-high transition
		_delay_us(200);                                 // Wait for character execution time
		LCD_Port = (LCD_Port & 0x0F) | (str[i] << 4);    // Send low nibble of character
		LCD_Port |= (1<<ENPIN);                          // Enable LCD (EN = 1) for high-to-low transition
		_delay_us(1);                                   // Wait for enable pulse width
		LCD_Port &= ~(1<<ENPIN);                         // Disable LCD (EN = 0) for low-to-high transition
		_delay_ms(2);                                   // Wait for character execution time
	}
}

// Function to print a string on the LCD at a specific position
void LCD_Printpos (char row, char pos, char *str)
{
	if (row == 0 && pos<16)
		LCD_Action((pos & 0x0F) | 0x80);  // Set cursor to the specified position on the first line
	else if (row == 1 && pos<16)
		LCD_Action((pos & 0x0F) | 0xC0);  // Set cursor to the specified position on the second line
	LCD_Print(str);                       // Print the string
}

int main()
{
	LCD_Init();                            // Initialize the LCD
	LCD_Print("Fahim Riaz Imran");         // Print initial message
	
	while (1)
	{
		LCD_Printpos(0, 0, "Fahim Riaz Imran");  // Print on the first line
		_delay_ms(500);                         // Delay for 500ms
		LCD_Printpos(1, 0, "are Friends");       // Print on the second line
		_delay_ms(500);                         // Delay for 500ms
		LCD_Clear();                            // Clear the LCD display
	}
	
	while (1)
		;  // Infinite loop to keep the program running
	
	return 0;
}
