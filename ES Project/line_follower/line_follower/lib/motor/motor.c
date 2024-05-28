/******************************************************************************

                          eXtreme Electronics xAPI(TM)
						  ----------------------------
xAPI is a Powerful but easy to use C library to program the xBoard(TM)
series of AVR development board. The library has support for commonly use tasks
like:-

*LCD interfacing
*MUXED 7 segment displays.
*Remote Control
*Serial Communication
*DC Motor Controls with Speed Control
*Analog Measurement for Sensor Interface.
*Temperature Measurement.
*I2C Communication.
*EEPROM Interface
*Real Time Clock (RTC Interface)

The APIs are highly documented and easy to use even by a beginner.

For More Info Log On to 
www.eXtremeElectronics.co.in

Copyright 2008-2009 eXtreme Electronics India

                                 DC Motor Core
						        ---------------------
This module is used for controlling DC motors via the on board L298 driver IC
The library has functions to control both the direction and speed of DC motors.
The PWM speed controlled is done by the library internally.


Please give credit to www.eXtremeElectronics.co.in if you use
it in your projects and find it useful

                                     NOTICE
									--------
NO PART OF THIS WORK CAN BE COPIED, DISTRIBUTED OR PUBLISHED WITHOUT A
WRITTEN PERMISSION FROM EXTREME ELECTRONICS INDIA. THE LIBRARY, NOR ANY PART
OF IT CAN BE USED IN COMMERCIAL APPLICATIONS. IT IS INTENDED TO BE USED FOR
HOBBY, LEARNING AND EDUCATIONAL PURPOSE ONLY. IF YOU WANT TO USE THEM IN 
COMMERCIAL APPLICATION PLEASE WRITE TO THE AUTHOR.


WRITTEN BY:
AVINASH GUPTA
me@avinashgupta.com


*******************************************************************************/

#include <avr/io.h>
#include <avr/interrupt.h>

#include "myutils.h"
#include "motor.h"

#define XBOARD2

void MotorInit()
{
	#ifdef XBOARD2

	//set up pwm for speed control

	TCCR1A=(1<<COM1A1)|(1<<COM1B1)|(1<<WGM10);

	//clk=fcpu/64

	TCCR1B=(1<<CS11)|(1<<CS10);

	//Set the corresponding port pin to output

	DDR(OC1A_PORT)|=(1<<OC1A_PIN);
	DDR(OC1B_PORT)|=(1<<OC1B_PIN);

	//Set the direction control PINs to OUT
	DDRD|=0X0F;	//PC0 to PC3 as output
	
	#endif
	
	#ifdef FIREBIRDV
	
	//Set up timer 5 for PWM
	
	TCCR5B = 0x00;	//Stop
	
	TCNT5H = 0xFF;	//Counter higher 8-bit value to which OCR5xH value is compared with
	TCNT5L = 0x01;	//Counter lower 8-bit value to which OCR5xH value is compared with
	
	OCR5AH = 0x00;	//Output compare register high value for Left Motor
	OCR5AL = 0xFF;	//Output compare register low value for Left Motor
	
	OCR5BH = 0x00;	//Output compare register high value for Right Motor
	OCR5BL = 0xFF;	//Output compare register low value for Right Motor
	
	OCR5CH = 0x00;	//Output compare register high value for Motor C1
	OCR5CL = 0xFF;	//Output compare register low value for Motor C1
	
	TCCR5A = 0xA9;	/*{COM5A1=1, COM5A0=0; COM5B1=1, COM5B0=0; COM5C1=1 COM5C0=0}
 					  For Overriding normal port functionalit to OCRnA outputs.
				  	  {WGM51=0, WGM50=1} Along With WGM52 in TCCR5B for Selecting FAST PWM 8-bit Mode*/
	
	TCCR5B = 0x0B;	//WGM12=1; CS12=0, CS11=1, CS10=1 (Prescaler=64)
	
	//Set PWM Pins to out
	DDRL|=(1<<PL3)|(1<<PL4);
	
	//Set Direction Pins to output
	DDRA|=(0x0F);
	
	#endif
	

}

/**********************************************************
Descriptipn:
	Set the rotation of motor A(LEFT) in given direction and speed

dir = 0 for stop
dir = 1 for CW rotation
dir = 2 for CCW rotation
dir = 3 for brake

speed is any value between 0 and 255

Example:
	MotorA(MOTOR_CW,120);

Note:
	Other Constants for direction are
	MOTOR_CCW and MOTOR_STOP

***********************************************************/
void MotorA(uint8_t dir,uint8_t speed)//LEFT
{
	#ifdef XBOARD2
	//Direction
	if(dir == MOTOR_STOP)
	{
		PORTD&=(~(1<<PD0));
		PORTD&=(~(1<<PD1));
	}

	else if(dir == MOTOR_CCW)
	{
		PORTD&=(~(1<<PD0));
		PORTD|=(1<<PD1);
	}
	else if(dir == MOTOR_CW)
	{
		PORTD&=(~(1<<PD1));
		PORTD|=(1<<PD0);
	}

	//Speed
	uint8_t sreg=SREG;

	cli();

	OCR1A=(uint8_t)(((float)speed/255.0)*ROBO_SPEED);

	SREG=sreg;
	#endif
	
	#ifdef FIREBIRDV
	//Direction
	if(dir == MOTOR_STOP)
	{
		PORTA&=(~(1<<PA0));
		PORTA&=(~(1<<PA1));
	}

	else if(dir == MOTOR_CCW)//forword
	{
		PORTA&=(~(1<<PA0));
		PORTA|=(1<<PA1);
	}
	else if(dir == MOTOR_CW)//back
	{
		PORTA&=(~(1<<PA1));
		PORTA|=(1<<PA0);
	}

	//Speed
	OCR5AL=(uint8_t)(((float)speed/255.0)*ROBO_SPEED);
	#endif
	
}

/**********************************************************
Descriptipn:
	Set the rotation of motor B in given direction and speed

dir = 0 for stop
dir = 1 for CW rotation
dir = 2 for CCW rotation
dir = 3 for brake

speed is any value between 0 and 255

Example:
	MotorB(MOTOR_CW,120);

Note:
	Other Constants for direction are
	MOTOR_CCW and MOTOR_STOP

***********************************************************/
void MotorB(uint8_t dir,uint8_t speed)//RIGHT
{
	#ifdef XBOARD2
	//Direction
	if(dir == MOTOR_STOP)
	{
		PORTD&=(~(1<<PD2));
		PORTD&=(~(1<<PD3));
	}

	else if(dir == MOTOR_CCW)
	{
		PORTD&=(~(1<<PD2));
		PORTD|=(1<<PD3);
	}
	else if(dir == MOTOR_CW)
	{
		PORTD&=(~(1<<PD3));
		PORTD|=(1<<PD2);
	}

	//Speed
	uint8_t sreg=SREG;

	cli();

	OCR1B=(uint8_t)(((float)speed/255.0)*ROBO_SPEED);

	SREG=sreg;
	#endif
	
	#ifdef FIREBIRDV
	//Direction
	if(dir == MOTOR_STOP)
	{
		PORTA&=(~(1<<PA2));
		PORTA&=(~(1<<PA3));
	}

	else if(dir == MOTOR_CCW)//back
	{
		PORTA&=(~(1<<PA2));
		PORTA|=(1<<PA3);
	}
	else if(dir == MOTOR_CW)//forword
	{
		PORTA&=(~(1<<PA3));
		PORTA|=(1<<PA2);
	}

	//Speed
	OCR5BL=(uint8_t)(((float)speed/255.0)*ROBO_SPEED);
	#endif
}
	
