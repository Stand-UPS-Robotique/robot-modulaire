#include "motor.h"

static unsigned char pwm_motor[MOTOR_SIZE]= {0, 0, 0, 0};

void init_motor(void)
{
    /* config pins as output */
    DDRD |= ((1 << PD3) | (1 << PD5) | (1 << PD6));
    DDRB |= (1 << PB3);

    /* deactivate global interruption */
    cli();

    /* config timer2 no prescaler, CTC (mode 2) */
    TCCR2A = (1 << WGM21);
    TCCR2B = (1 << CS20);

    /* activate local interruption */
    TIMSK2 = (1 << OCIE2A);

    /* config OCR2A to generate 256 interruptions in period pwm motor */
    OCR2A = PERIOD_PWM_MOTOR / (256.0 * 1000.0 / F_CPU);

    /* activate global interruption */
    sei();
}

void write_pwm_motor(unsigned char idx, unsigned char pwm_value)
{
    if(idx >=0 && idx < MOTOR_SIZE)
    {
        pwm_motor[idx] = pwm_value;
    }
}

ISR(TIMER2_COMPA_vect)
{
    static unsigned int period_counter = 0;
    
    /* set high all pwm motors when a new cycle starts */
    if(period_counter == 0)
    {
        PORTD |= (1 << PD3 | 1 << PD5 | 1 << PD6);
        PORTB |= (1 << PB3);
    }

    /* set low a pwm motor when a his value is reached */
    if(period_counter == pwm_motor[0])
    {
        PORTD &= (~(1 << PD3));
    }

     if(period_counter == pwm_motor[1])
    {
        PORTD &= (~(1 << PD5));
    }

     if(period_counter == pwm_motor[2])
    {
        PORTD &= (~(1 << PD6));
    }

     if(period_counter == pwm_motor[3])
    {
        PORTB &= (~(1 << PB3));
    }

    /* increment counter */
    period_counter++;

    /* reset counter when a cycle is completed */
    if(period_counter == 255)
    {
        period_counter = 0;
    }
}