#include <avr/io.h>
#define  F_CPU 16000000UL
#include <util/delay.h>


#define MOTOR_1_PORT PORTB
#define MOTOR_1_PIN PB0
#define MOTOR_2_PORT PORTB
#define MOTOR_2_PIN PB5
#define Led_1_front_Port PORTB
#define led_1_front_pin PB4
#define led_2_front_pin PB1
#define led_back_port PORTB
#define led_back_pin PB3
#define buzzer_port PORTC
#define buzzer_pin PC3
#define hitting_motor PC5

void obstacles(){
	PORTB &= ~(1<<led_1_front_pin);
	PORTB &= ~(1<<led_2_front_pin);
	// Stop motors
	PORTB &= ~(1 << MOTOR_1_PIN) & ~(1 << MOTOR_2_PIN);
	PORTB |= (1<<led_back_pin);

	// Wait 2 seconds
	_delay_ms(2000);
	PORTC |= (1<<hitting_motor);
	_delay_ms(8000);
	
	PORTB &= ~(1<<led_back_pin);
	PORTC &= ~(1<<hitting_motor);
	

}


void motor_forward()
{
	// back led
	PORTB &= ~(1<<led_back_pin);
	// buzzer
	PORTC &= ~(1<<buzzer_pin);
	
	// Start motors again
	PORTB |= (1 << MOTOR_1_PIN) | (1 << MOTOR_2_PIN);
	PORTB |= (1<<led_1_front_pin);
	PORTB |= (1<<led_2_front_pin);
}
int main(void) {
	// Set motor and led ports as output
	DDRB |= (1 << MOTOR_1_PIN) | (1 << MOTOR_2_PIN) | (1<<led_1_front_pin)| (1<<led_2_front_pin) | (1<<led_back_pin) ;
	DDRC |= (1 << buzzer_pin)|(1<<hitting_motor);

	// Start motors
	//PORTB |= (1 << MOTOR_1_PIN) | (1 << MOTOR_2_PIN);
	
			do {
				// Wait for object to be detected
				if ((PINC & (1 << PC0))==0) {
					obstacles();
				}
			 /*	if((PINC & (1 << PC2 )) ==0)
				{
					// Motor 1 stop
					PORTB &= ~(1 << MOTOR_1_PIN);
					// Motor 2 stop
					PORTB &= ~(1 << MOTOR_2_PIN);
					// back led
					PORTB |= (1<<led_back_pin);
					// buzzer
					PORTC |= (1<<buzzer_pin);
					PORTB &= ~(1<<led_1_front_pin);
					PORTB &= ~(1<<led_2_front_pin);
				} 
				else*/
			   if ((PINC & (1 << PC1)) )
				{
					// back led
					PORTB &= ~(1<<led_back_pin);
					// buzzer
					PORTC &= ~(1<<buzzer_pin);
					
					PORTB |= (1<<led_1_front_pin);
					PORTB |= (1<<led_2_front_pin);
					
					// Motor 1 start
					PORTB |= (1 << MOTOR_1_PIN);
					
					// Motor 2 stop
					PORTB &= ~(1 << MOTOR_2_PIN);
					
				}
				else if ((PINB & (1<<PB2)))
				{
					// back led
					PORTB &= ~(1<<led_back_pin);
					// buzzer
					PORTC &= ~(1<<buzzer_pin);
					
					PORTB |= (1<<led_1_front_pin);
					PORTB |= (1<<led_2_front_pin);
					
					
					// Motor 1 stop
					PORTB &= ~(1 << MOTOR_1_PIN);
					
					// Motor 2 start
					PORTB |= (1 << MOTOR_2_PIN);
					
					
				}
				else
				motor_forward();
				

			} while (1);
	

}