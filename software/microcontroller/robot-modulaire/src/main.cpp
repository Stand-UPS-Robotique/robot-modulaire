#include <Arduino.h>
#include "motor.h"
#include "servo.h"
#include "adc.h"
#include "battery_sensor.h"

void setup() 
{
  Serial.begin(9600);
  init_motor();
  init_servo();
  init_adc();
  init_battery_sensor();
}

void loop() 
{
  Serial.print("voltage: ");
  Serial.println(get_voltage_battery_sensor());
  Serial.print("rate: ");
  Serial.println(get_rate_battery_sensor());

  for(int i = 0; i <= 180; i++)
  {
    write_pwm_servo(0, i);
    write_pwm_servo(1, 180 - i);
    delay(50);
  }
  
}