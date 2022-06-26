#include <Arduino.h>

#include <avr/interrupt.h>
#include "motor.h"
#include "ultrasonic_sensor.h"

ISR(TIMER2_COMPA_vect)
{
    handle_counter_interrupt_ultrasonic_sensor();
    handle_interrupt_motor();
}