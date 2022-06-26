#ifndef MOTOR_H
#define MOTOR_H

#include <Arduino.h>

#define SIZE_MOTOR          4
#define PERIOD_PWM_MOTOR    2
#define MIN_PWM_MOTOR       0
#define MAX_PWM_MOTOR       255

void init_motor(void);
void write_pwm_motor(unsigned char idx, unsigned char pwm_value, unsigned char sense);

#endif