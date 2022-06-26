#include <Arduino.h>
#include "motor.h"
#include "servo.h"
#include "adc.h"
#include "battery_sensor.h"
#include "bluetooth.h"

void setup() 
{
  Serial.begin(9600);
  init_bluetooth();
  init_motor();
  init_servo();
  init_adc();
  init_battery_sensor();
}

void loop() 
{
  // Serial.print("voltage: ");
  // Serial.println(get_voltage_battery_sensor());
  // Serial.print("rate: ");
  // Serial.println(get_rate_battery_sensor());

  update_bluetooth();

  Serial.print(data_cmd.joy_x);
  Serial.print(",");
  Serial.print(data_cmd.joy_y);
  Serial.print(",");
  Serial.print(data_cmd.slide_x);
  Serial.print(",");
  Serial.println(data_cmd.slide_y);

  write_pwm_motor(0, data_cmd.joy_x, data_cmd.joy_y);
}