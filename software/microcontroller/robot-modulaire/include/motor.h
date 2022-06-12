#ifndef MOTOR_H
#define MOTOR_H

#include "Arduino.h"

#define MOTOR_SIZE 4
#define PERIOD_PWM_MOTOR 2


void init_motor(void);
void write_pwm_motor(unsigned char idx, unsigned char pwm_value);

#endif