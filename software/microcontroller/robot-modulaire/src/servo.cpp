#include "servo.h"

static unsigned char buffer_pwm_servo[SIZE_SERVO]= {0, 0};

void init_servo(void)
{
/* config pins as output */
    DDRB |= ((1 << PB1) | (1 << PB2));

    /* deactivate global interruption */
    cli();

    /* config timer1 prescaler by 64, fast pwm mode 9 bits */
    TCCR1A = ((1 << WGM11) | (1 << COM1A0) | (1 << COM1A1) | (1 << COM1B0) | (1 << COM1B1));
    TCCR1B = ((1 << WGM12) | (1 << CS10) | (1 << CS11));

    /* activate local interruption of overflow */
    TIMSK1 = (1 << TOIE1);

    /* init OCR1A and OCR1B */
    OCR1A = 0;
    OCR1B = 0;

    /* activate global interruption */
    sei();
}

void write_pwm_servo(unsigned char idx, float angle)
{
    if(idx >=0 && idx < SIZE_SERVO)
    {
        if(angle >= MIN_ANGLE_SERVO && angle <= MAX_ANGLE_SERVO)
        {
            int value = (angle / 180.0 + PERIOD_PWM_SERVO / 2.0) / PERIOD_PWM_SERVO * (SAMPLES_PWM_SERVO - 1.0);
            buffer_pwm_servo[idx] = value;
        }
    }
}

ISR(TIMER1_OVF_vect)
{
    /* update duty cycle of servos pwm */
    OCR1A = buffer_pwm_servo[0];
    OCR1B = buffer_pwm_servo[1];
}