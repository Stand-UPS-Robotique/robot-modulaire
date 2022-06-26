#ifndef SERVO_H
#define SERVO_H

#include <avr/interrupt.h>

#define SIZE_SERVO              2
#define T_0_SERVO               1.0
#define TIME_2_NUMS_SERVO       1000
#define MIN_ANGLE_SERVO         0.0
#define MAX_ANGLE_SERVO         180.0

void init_servo(void);
void write_pwm_servo(unsigned char idx, float angle);

#endif