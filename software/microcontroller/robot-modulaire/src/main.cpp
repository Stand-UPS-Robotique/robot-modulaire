#include <Arduino.h>
#include "motor.h"
#include "servo.h"
#include "adc.h"
#include "battery_sensor.h"
#include "bluetooth.h"
#include "ultrasonic_sensor.h"
#include "ir_sensor.h"

void control_omniwheels()
{
  /* variables */
  static int x_mot = 0, y_mot = 0;

  static unsigned char left_up_mot = 0, left_up_sense = 0;
  static unsigned char left_down_mot = 0, left_down_sense = 0;
  static unsigned char right_up_mot = 0, right_up_sense = 0;
  static unsigned char right_down_mot = 0, right_down_sense = 0;

  /* read data bluetooth */
  update_bluetooth();

  /* convert x_joy and y_joy to control motors */
  y_mot = 2 * (data_cmd.joy_y - 127) - 1;
  x_mot = 2 * (data_cmd.joy_x - 127) - 1;
  x_mot += y_mot;


  /* deduce senses */
  if(x_mot < 0)
  {
    left_up_sense = 0;
    right_up_sense = 1;
    left_down_sense = 1;
    right_down_sense = 0;
  }
  else
  {
    left_up_sense = 1;
    right_up_sense = 0;
    left_down_sense = 0;
    right_down_sense = 1;
  }

  /* compute pwm values */
  left_up_mot = 


  /* write motors */
  write_pwm_motor(0, right_up_mot, right_up_sense);
  write_pwm_motor(1, left_up_mot, left_up_sense);
  write_pwm_motor(2, right_down_mot, right_up_sense);
  write_pwm_motor(3, left_down_mot, left_down_sense);
}

void setup() 
{
  Serial.begin(9600);

  init_bluetooth();
  init_motor();
  init_servo();
  init_adc();
  init_battery_sensor();
  init_ultrasonic_sensor();
  init_ir_sensor();
}

void loop() 
{
  // Serial.print("voltage: ");
  // Serial.println(get_voltage_battery_sensor());
  // Serial.print("rate: ");
  // Serial.println(get_rate_battery_sensor());

  control_omniwheels();

  Serial.print(data_cmd.joy_x);
  Serial.print(",");
  Serial.print(data_cmd.joy_y);
  Serial.print(",");
  Serial.print(data_cmd.slide_x);
  Serial.print(",");
  Serial.println(data_cmd.slide_y);

  // Serial.print("IR1: ");
  // Serial.print(get_distance_ir_sensor(0));
  // Serial.print("\tIR2: ");
  // Serial.println(get_distance_ir_sensor(1));
}