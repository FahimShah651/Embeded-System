/*
   This code is written for an AVR microcontroller to interface with an ultrasonic sensor and display the measured distance on a 16x2 character LCD.
*/

#define F_CPU 800000UL // Define the clock frequency for delay functions
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <string.h>
#include <stdlib.h>

// Define LCD control pins and trigger pin for the ultrasonic sensor
#define Trigger_pin PB1
#define LCD_Port PORTD
#define LCD_DPin DDRD
#define RSPIN PD0
#define ENPIN PD1

int TimerOverflow = 0; // Counter for Timer1 overflows

// Interrupt service routine for Timer1 overflow
ISR(TIMER1_OVF_vect)
{
    TimerOverflow++;
}

// Function to send a command to the LCD
void LCD_Action(unsigned char cmnd)
{
    LCD_Port = (LCD_Port & 0x0F) | (cmnd & 0xF0); // Send upper nibble
    LCD_Port &= ~(1 << RSPIN); // Select command register (RS = 0)
    LCD_Port |= (1 << ENPIN); // Enable high pulse
    _delay_us(1);
    LCD_Port &= ~(1 << ENPIN); // Disable the enable pin
    _delay_us(200);

    LCD_Port = (LCD_Port & 0x0F) | (cmnd << 4); // Send lower nibble
    LCD_Port |= (1 << ENPIN); // Enable high pulse
    _delay_us(1);
    LCD_Port &= ~(1 << ENPIN); // Disable the enable pin
    _delay_ms(2);
}

// Function to initialize the LCD
void LCD_Init(void)
{
    LCD_DPin = 0xFF; // Set data direction of the LCD port to output
    _delay_ms(15);
    LCD_Action(0x33); // Initialize the LCD in 4-bit mode
    LCD_Action(0x32);
    LCD_Action(0x28); // 4-bit mode, 2 lines, 5x8 font
    LCD_Action(0x02); // Return home (reset the cursor position)
    LCD_Action(0x0C); // Display on, cursor off
    LCD_Action(0x06); // Entry mode: Increment cursor, no display shift
    LCD_Action(0x01); // Clear the display
    _delay_ms(2);
}

// Function to clear the LCD display
void LCD_Clear()
{
    LCD_Action(0x01); // Clear the display
    _delay_ms(2);
    LCD_Action(0x80); // Move the cursor to the first position of the first line
}

// Function to print a string on the LCD
void LCD_Print(char *str)
{
    int i;
    for (i = 0; str[i] != 0; i++)
    {
        LCD_Port = (LCD_Port & 0x0F) | (str[i] & 0xF0); // Send upper nibble of the character
        LCD_Port |= (1 << RSPIN); // Select data register (RS = 1)
        LCD_Port |= (1 << ENPIN); // Enable high pulse
        _delay_us(1);
        LCD_Port &= ~(1 << ENPIN); // Disable the enable pin
        _delay_us(200);

        LCD_Port = (LCD_Port & 0x0F) | (str[i] << 4); // Send lower nibble of the character
        LCD_Port |= (1 << ENPIN); // Enable high pulse
        _delay_us(1);
        LCD_Port &= ~(1 << ENPIN); // Disable the enable pin
        _delay_ms(2);
    }
}

// Function to print a string at a specific position on the LCD
void LCD_Printpos(char row, char pos, char *str)
{
    if (row == 0 && pos < 16)
        LCD_Action((pos & 0x0F) | 0x80); // Move the cursor to the specified position on the first line
    else if (row == 1 && pos < 16)
        LCD_Action((pos & 0x0F) | 0xC0); // Move the cursor to the specified position on the second line
    LCD_Print(str);
}

int main(void)
{
    char string[10];
    long count;
    double distance;

    DDRB |= (1 << PORTB1); // Set Trigger_pin as output
    DDRB &= ~(1 << PORTB0); // Set PORTB0 (Echo pin) as input
    PORTB |= (1 << PORTB0); // Enable internal pull-up for PORTB0

    LCD_Init(); // Initialize the LCD
    LCD_Printpos(0, 0, "Ultrasonic"); // Display "Ultrasonic" on the first line of the LCD

    sei(); // Enable global interrupts
    TIMSK1 = (1 << TOIE1); // Enable Timer1 overflow interrupt
    TCCR1A = 0; // Timer1 control register A (not used in this application)

    while (1)
    {
        PORTB |= (1 << Trigger_pin); // Generate a trigger pulse
        _delay_us(12);
        PORTB &= ~(1 << Trigger_pin); // Stop the trigger pulse

        TCNT1 = 0; // Clear Timer1 count
        TCCR1B = 0x41; // Start Timer1 with prescaler 64
        TIFR1 = 1 << ICF1; // Clear Input Capture Flag
        TIFR1 = 1 << TOV1; // Clear Timer1 Overflow Flag

        while ((TIFR1 & (1 << ICF1)) == 0); // Wait for the rising edge on Echo pin
        TCNT1 = 0; // Clear Timer1 count
        TCCR1B = 0x01; // Start Timer1 with no prescaler
        TIFR1 = 1 << ICF1; // Clear Input Capture Flag
        TIFR1 = 1 << TOV1; // Clear Timer1 Overflow Flag
        TimerOverflow = 0; // Reset TimerOverflow counter

        while ((TIFR1 & (1 << ICF1)) == 0); // Wait for the falling edge on Echo pin
        count = ICR1 + (65535 * TimerOverflow); // Calculate the total count elapsed
        distance = (double)count / 466.47; // Calculate the distance in centimeters

        dtostrf(distance, 2, 2, string); // Convert the distance value to a string
        strcat(string, " cm   "); // Concatenate " cm" to the distance value
        LCD_Printpos(1, 0, "Dist = "); // Display "Dist = " on the second line of the LCD
        LCD_Printpos(1, 7, string); // Display the distance value on the LCD
        _delay_ms(500); // Delay before taking the next measurement
    }
}
