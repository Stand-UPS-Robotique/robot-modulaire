#ifndef SERVO_H
#define SERVO_H

#include "Arduino.h"

#define SIZE_SERVO              2
#define PERIOD_PWM_SERVO        2
#define SAMPLES_PWM_SERVO       512
#define MIN_ANGLE_SERVO         0
#define MAX_ANGLE_SERVO         180

void init_servo(void);
void write_pwm_servo(unsigned char idx, float angle);

#endif