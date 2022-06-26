#include <avr/interrupt.h>
#include "ultrasonic_sensor.h"
#include "bluetooth.h"

ISR(INT0_vect)
{
    handle_flag_interrupt_ultrasonic_sensor();
}