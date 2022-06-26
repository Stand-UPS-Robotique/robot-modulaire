#include "bluetooth.h"

SoftwareSerial serial_bluetooth(BL_RX_PIN, BL_TX_PIN);
data_bluetooth data_cmd = {0, 0, 0, 0};

void init_bluetooth(void)
{
    /* setup pinout */
    DDRD |= (1 << PD7);
    DDRB = (DDRB & (~(1 << PB0)));

    /* setup serial */
    serial_bluetooth.begin(BAUDRATE_BLUETOOTH);
}

void update_bluetooth(void)
{
    /* statements */
    static int state = INIT_STATE;
    static int value = 0;
    static int counter = 0;
    char c;

    /* state machine */
    if(serial_bluetooth.available() > 0)
    {
        c = serial_bluetooth.read();

        switch(state)
        {
        case INIT_STATE:
            if(c == '\n')
            {
                state = JOY_X_STATE;
                value = 0;
                counter = 0;
            }
            break;
        
        case JOY_X_STATE:
            if(counter < 3)
            {
                if(c >= '0' && c <= '9')
                {
                    value = value * 10 + (c - '0');
                    counter++;
                }
                else
                {
                    state = INIT_STATE;
                }
            }
            else
            {
                if(c == SEPARATOR_CMD)
                {
                    state = JOY_Y_STATE;
                    data_cmd.joy_x = value;
                    value = 0;
                    counter = 0;
                }
                else
                {
                    state = INIT_STATE;
                }
            }
            break;
        
        case JOY_Y_STATE:
            if(counter < 3)
            {
                if(c >= '0' && c <= '9')
                {
                    value = value * 10 + (c - '0');
                    counter++;
                }
                else
                {
                    state = INIT_STATE;
                }
            }
            else
            {
                if(c == SEPARATOR_CMD)
                {
                    state = SLIDER_X_STATE;
                    data_cmd.joy_y = value;
                    value = 0;
                    counter = 0;
                }
                else
                {
                    state = INIT_STATE;
                }
            }
            break;

        case SLIDER_X_STATE:
            if(counter < 3)
            {
                if(c >= '0' && c <= '9')
                {
                    value = value * 10 + (c - '0');
                    counter++;
                }
                else
                {
                    state = INIT_STATE;
                }
            }
            else
            {
                if(c == SEPARATOR_CMD)
                {
                    state = SLIDER_Y_STATE;
                    data_cmd.slide_x = value;
                    value = 0;
                    counter = 0;
                }
                else
                {
                    state = INIT_STATE;
                }
            }
            break;

        case SLIDER_Y_STATE:
            if(counter < 3)
            {
                if(c >= '0' && c <= '9')
                {
                    value = value * 10 + (c - '0');
                    counter++;
                }
                else
                {
                    state = INIT_STATE;
                }
            }
            else
            {
                if(c == '\n')
                {
                    state = JOY_X_STATE;
                    data_cmd.slide_y = value;
                    value = 0;
                    counter = 0;
                }
                else
                {
                    state = INIT_STATE;
                }
            }
            break;
        
        default:
            break;
        }
    }
}