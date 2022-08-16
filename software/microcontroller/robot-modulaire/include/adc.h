#ifndef ADC_H
#define ADC_H

#include <avr/interrupt.h>
#include "battery_sensor.h"
#include "ir_sensor.h"

#define ID_OFFSET_ADC       4
#define USED_PERIPH_ADC     3

#define MIN_VOLTAGE_ADC     0.0
#define MAX_VOLTAGE_ADC     5.0

#define MIN_VALUE_ADC       0.0
#define MAX_VALUE_ADC       1023.0

void init_adc(void);

#endif