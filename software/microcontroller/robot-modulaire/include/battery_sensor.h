#ifndef BATTERY_SENSOR_H
#define BATTERY_SENSOR_H

#include <avr/interrupt.h>
#include "adc.h"

#define RATIO_BATTERY       0.58892815076
#define MIN_VOLTAGE_BATTERY 5.6
#define MAX_VOLTAGE_BATTERY 8.4
#define SAMPLES_BATTERY     5

extern char counter_battery;
extern float adc_battery[SAMPLES_BATTERY];

void init_battery_sensor(void);
void update_battery_sensor(int sample);
float get_voltage_battery_sensor(void);
float get_rate_battery_sensor(void);

#endif