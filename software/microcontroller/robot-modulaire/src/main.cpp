#include <Arduino.h>
#include "motor.h"

void setup() 
{
  init_motor();
}

void loop() 
{
  for(int i = 0; i < 255; i++)
  {
    write_pwm_motor(0, i);
    write_pwm_motor(1, 255 - i);
    write_pwm_motor(2, i);
    write_pwm_motor(3, 255 - i);
    delay(100);
  }

  for(int i = 255; i > 0; i--)
  {
    write_pwm_motor(0, i);
    write_pwm_motor(1, 255 - i);
    write_pwm_motor(2, i);
    write_pwm_motor(3, 255 - i);
    delay(100);
  }
}