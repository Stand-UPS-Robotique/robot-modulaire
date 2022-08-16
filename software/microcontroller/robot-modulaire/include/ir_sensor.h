#ifndef IR_SENSOR_H
#define IR_SENSOR_H

#include <math.h>

#define SIZE_IR_SENSOR          2
#define SAMPLES_IR_SENSOR       5

#define K                       29.988
#define P                       -1.173

#define MAX_ADC_VALUE           1023.0
#define MAX_VOLTAGE             5.0

extern char counter_ir_sensor[SIZE_IR_SENSOR];
extern float adc_ir_sensor[SIZE_IR_SENSOR][SAMPLES_IR_SENSOR];

void init_ir_sensor(void);
void update_ir_sensor(char idx, int sample);
float get_distance_ir_sensor(char idx);

#endif