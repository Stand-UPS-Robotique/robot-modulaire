#include "ir_sensor.h"

char counter_ir_sensor[SIZE_IR_SENSOR];
float adc_ir_sensor[SIZE_IR_SENSOR][SAMPLES_IR_SENSOR];

void init_ir_sensor(void)
{
    int i;
    int j;

    for(j = 0; j < SIZE_IR_SENSOR; j++)
    {
        counter_ir_sensor[j] = 0;

        for(i = 0; i < SAMPLES_IR_SENSOR; i++)
        {
            adc_ir_sensor[j][i] = 0.0;
        }
    }
}

void update_ir_sensor(char idx, int sample)
{
    if(idx == 0 || idx == 1)
    {
        idx ^= 1;
        adc_ir_sensor[idx][counter_ir_sensor[idx]] = sample;
        counter_ir_sensor[idx]++;

        if(counter_ir_sensor[idx] == SAMPLES_IR_SENSOR)
        {
            counter_ir_sensor[idx] = 0;
        }
    }
}

float get_distance_ir_sensor(char idx)
{
    float samples_average;
    int i;
    
    samples_average = 0;

     if(idx == 0 || idx == 1)
     {
        idx ^= 1;
        for(i = 0; i < SAMPLES_IR_SENSOR; i++)
        {
            samples_average += adc_ir_sensor[idx][i];
        }

        samples_average /= ((float) SAMPLES_IR_SENSOR);
     }

    return K * pow(samples_average / MAX_ADC_VALUE * MAX_VOLTAGE, P);
}