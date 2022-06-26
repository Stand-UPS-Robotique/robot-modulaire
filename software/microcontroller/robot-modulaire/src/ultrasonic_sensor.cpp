#include <Arduino.h>

#include "ultrasonic_sensor.h"

int passed_ticks_ultrasonic_sensor = 0L;
char flag_ultrasonic_sensor = 0x0;

void init_ultrasonic_sensor(void)
{
    /* setup echo pin as input and trig pin as output */
    DDRD |= (1 << PD4);
    DDRD = (DDRD & (~(1 << PD2)));

    /* deactivate global interruption */
    cli();

    /* configure external interrupt on PCINT20 (digital pin 4) */
    EICRA = (1 << ISC01);
    EIMSK |= (1 << INT0);

    /* activate global interruption */
    sei();
}

float get_distance_ultrasonic_sensor(void)
{
    /* generate pulse on trig pin during 10 us */
    PORTD |= (1 << PD4);
    _delay_us(10);
    PORTD = (PORTD & (~(1 << PD4)));

    /* wait flag ultrasonic sensor */
    passed_ticks_ultrasonic_sensor = 0;
    flag_ultrasonic_sensor = 0x1;
    while(flag_ultrasonic_sensor == 0x1)
    {
        Serial.print(".");
    }

    /* compute distance */
    return (passed_ticks_ultrasonic_sensor * (125.0 / F_CPU) / 2.0 * SOUND_SPEED);
}

void handle_counter_interrupt_ultrasonic_sensor(void)
{
    if(flag_ultrasonic_sensor == 0x1)
    {
        passed_ticks_ultrasonic_sensor++;
        if(passed_ticks_ultrasonic_sensor > 4000)
        {
            flag_ultrasonic_sensor = 0x0;
        }
    }
}

void handle_flag_interrupt_ultrasonic_sensor(void)
{
    flag_ultrasonic_sensor = 0x0;
}