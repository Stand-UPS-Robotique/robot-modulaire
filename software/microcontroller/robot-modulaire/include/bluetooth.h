#ifndef BLUETOOTH_H
#define BLUETOOTH_H

#include <Arduino.h>
#include <SoftwareSerial.h>
#include "pinmap.h"

#define BAUDRATE_BLUETOOTH 9600

#define SEPARATOR_CMD ','

#define INIT_STATE 0
#define JOY_X_STATE 1
#define JOY_Y_STATE 2
#define SLIDER_X_STATE 3
#define SLIDER_Y_STATE 4

typedef struct
{
    unsigned int joy_x;
    unsigned int joy_y;
    unsigned int slide_x;
    unsigned int slide_y;
} data_bluetooth;

extern data_bluetooth data_cmd;

void init_bluetooth(void);
void configure_bluetooth(void);
void update_bluetooth(void);

#endif