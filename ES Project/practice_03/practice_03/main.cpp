#include <avr/io.h>
#include <util/delay.h>

#define F_CPU 16000000UL // 16MHz clock frequency
#define SERVO_MOTOR_PIN PD6

// Lookup table for servo motor angles and corresponding pulse width
const int servoAngles[] = {0, 45, 90, 135, 180, 225, 270, 315, 360};
const int pulseWidths[] = {500, 885, 1270, 1655, 2040, 2425, 2810, 3195, 3580};

void rotateServo(int angle);

int main() {
	// Set servo motor pin (PD6) as output
	DDRD |= (1 << SERVO_MOTOR_PIN);

	while (1) {
		// Rotate the servo motor 360 degrees in 45-degree steps
		for (int i = 0; i < sizeof(servoAngles) / sizeof(servoAngles[0]); i++) {
			rotateServo(servoAngles[i]);
			_delay_ms(1500);
		}
	}

	return 0;
}

void rotateServo(int angle) {
	// Angle value should be between 0 and 360 degrees
	if (angle < 0)
	angle = 0;
	else if (angle > 360)
	angle = 360;

	// Find the corresponding pulse width from the lookup table
	int pulse_width = pulseWidths[angle / 45];

	// Generate PWM signal to control the servo motor
	for (int i = 0; i < 50; i++) {
		// Set the servo motor pin high for the calculated pulse width duration
		PORTD |= (1 << SERVO_MOTOR_PIN);
		_delay_us(pulse_width);

		// Set the servo motor pin low for the remaining time
		PORTD &= ~(1 << SERVO_MOTOR_PIN);
		_delay_us(20000 - pulse_width);
	}
}
