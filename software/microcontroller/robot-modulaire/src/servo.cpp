#include "servo.h"

void init_servo(void)
{
/* config pins as output */
    DDRB |= ((1 << PB1) | (1 << PB2));

    /* deactivate global interruption */
    cli();

    /* config timer1 prescaler by 8, PWM, phase and frequency correct, frequency 50 Hz */
    TCCR1A = ((1 << COM1A1) | (1 << COM1B1));
    TCCR1B = ((1 << WGM13) | (1 << CS11));
    ICR1 = 20000;

    /* init OCR1A and OCR1B */
    OCR1A = 1000;
    OCR1B = 1000;

    /* activate global interruption */
    sei();
}

void write_pwm_servo(unsigned char idx, float angle)
{
    if(angle >= MIN_ANGLE_SERVO && angle <= MAX_ANGLE_SERVO)
    {
        int value = (angle / MAX_ANGLE_SERVO + T_0_SERVO) * TIME_2_NUMS_SERVO;

        switch(idx)
        {
            case 0:
                OCR1A = value;
                break;

            case 1:
                OCR1B = value;
                break;

            default:
                break;
        }
    }
}