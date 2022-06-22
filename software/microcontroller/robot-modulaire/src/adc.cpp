#include "adc.h"

/*
0100 (4) -> Vbat
0101 (5) -> IR1
0110 (6) -> IR2
*/
char id_adc;

void init_adc(void)
{
    /* deactivate global interruption */
    cli();

    /* setup first peripheral to read */
    id_adc = ID_OFFSET_ADC;

    /* select VREF as AVCC and select first channel to convert */
    ADMUX = ((1 << REFS0) | id_adc);

    /* enable ADC, enable interruption, start firdt conversion, set prescaler to 128 (16e6 / 128 = 125e3) */
    ADCSRA = ((1 << ADEN) | (1 << ADIE) | (1 << ADSC) | (1 << ADPS0) | (1 << ADPS1) | (1 << ADPS2));

    /* activate global interruption */
    sei();
}

ISR(ADC_vect)
{
    switch(id_adc)
    {
        case 4:
            update_battery_sensor(ADC);
            break;
        case 5:
            break;
        case 6:
            break;
    }
    
    id_adc++;
    if(id_adc == (ID_OFFSET_ADC + USED_PERIPH_ADC))
    {
        id_adc = ID_OFFSET_ADC;
    }
    ADMUX = ((1 << REFS0) | id_adc);
    ADCSRA |= (1 << ADSC);
}