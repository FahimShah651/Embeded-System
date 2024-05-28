#include <avr/io.h>


#ifndef MOTOR_H
#define MOTOR_H

#define OC1A_PORT B
#define OC1A_PIN PB1

#define OC1B_PORT B
#define OC1B_PIN PB2

#define MOTOR_STOP 	0
#define MOTOR_CW	1
#define MOTOR_CCW	2

#define ROBO_SPEED 200 //0-255

void MotorInit();
void MotorA(uint8_t dir,uint8_t speed);
void MotorB(uint8_t dir,uint8_t speed);

#endif
