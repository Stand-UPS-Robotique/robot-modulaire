#ifndef ULTRASONIC_SENSOR_H
#define ULTRASONIC_SENSOR_H

#include <avr/interrupt.h>
#include <util/delay.h>

#define SOUND_SPEED 300.0

extern int passed_ticks_ultrasonic_sensor;
extern char flag_ultrasonic_sensor;

void init_ultrasonic_sensor(void);
float get_distance_ultrasonic_sensor(void);
void handle_counter_interrupt_ultrasonic_sensor(void);
void handle_flag_interrupt_ultrasonic_sensor(void);

#endif