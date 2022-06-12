#include <Arduino.h>
#include "motor.h"
#include "servo.h"

void setup() 
{
  init_motor();
  init_servo();
}

void loop() 
{
  for(int i = 0; i < 255; i++)
  {
    write_pwm_motor(0, i);
    write_pwm_motor(1, 255 - i);
    write_pwm_motor(2, i);
    write_pwm_motor(3, 255 - i);
    delay(10);
  }

  for(int i = 255; i > 0; i--)
  {
    write_pwm_motor(0, i);
    write_pwm_motor(1, 255 - i);
    write_pwm_motor(2, i);
    write_pwm_motor(3, 255 - i);
    delay(10);
  }

  for(int i = 0; i < 180; i++)
  {
    write_pwm_servo(0, i);
    write_pwm_servo(1, 180 - i);
    delay(10);
  }

  for(int i = 180; i > 0; i--)
  {
    write_pwm_servo(0, i);
    write_pwm_servo(1, 180 - i);
    delay(10);
  }
}