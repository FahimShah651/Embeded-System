#include <avr/io.h>
#include <util/delay.h>

#define MOTOR_1_PORT PORTB
#define MOTOR_1_PIN PB0
#define MOTOR_2_PORT PORTB
#define MOTOR_2_PIN PB1
#define Led_front_Port PORTB
#define led_front_pin PB4
#define led_back_port PORTB
#define led_back_pin PB3

void obstacles(){
    PORTB &= ~(1<<led_front_pin);
	// Stop motors
	PORTB &= ~(1 << MOTOR_1_PIN) & ~(1 << MOTOR_2_PIN);
	PORTB |= (1<<led_back_pin);

	// Wait 2 seconds
	_delay_ms(2000);
	PORTB &= ~(1<<led_back_pin);

}

void motor_forward()
{
	// Start motors again
	PORTB |= (1 << MOTOR_1_PIN) | (1 << MOTOR_2_PIN);
	PORTB |= (1<<led_front_pin);

}
int main(void) {
	// Set motor and led ports as output 
	DDRB |= (1 << MOTOR_1_PIN) | (1 << MOTOR_2_PIN) | (1<<led_front_pin) | (1<<led_back_pin);

	// Start motors
	//PORTB |= (1 << MOTOR_1_PIN) | (1 << MOTOR_2_PIN);

	do {
		// Wait for object to be detected
		if (PINB & (1 << PB2)) {
			obstacles();
			  
		}

		motor_forward();
			
			
	} while (1);


}
