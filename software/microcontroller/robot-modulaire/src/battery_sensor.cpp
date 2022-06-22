#include "battery_sensor.h"

char counter_battery;
float adc_battery[SAMPLES_BATTERY];

void init_battery_sensor(void)
{
    int i;

    counter_battery = 0;

    for(i = 0; i < SAMPLES_BATTERY; i++)
    {
        adc_battery[i] = 0.0;
    }
}

void update_battery_sensor(int sample)
{
    adc_battery[counter_battery] = sample;
    counter_battery++;

    if(counter_battery == SAMPLES_BATTERY)
    {
        counter_battery = 0;
    }
}

float get_voltage_battery_sensor(void)
{
    float samples_average;
    int i;

    samples_average = 0;

    for(i = 0; i < SAMPLES_BATTERY; i++)
    {
        samples_average += adc_battery[i];
    }

    samples_average /= ((float) SAMPLES_BATTERY);

    return samples_average / MAX_VALUE_ADC * MAX_VOLTAGE_ADC / RATIO_BATTERY;
}

float get_rate_battery_sensor(void)
{
    return (get_voltage_battery_sensor() - MIN_VOLTAGE_BATTERY) / (MAX_VOLTAGE_BATTERY - MIN_VOLTAGE_BATTERY) * 100.0;
}