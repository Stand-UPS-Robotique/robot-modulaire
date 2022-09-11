#include <Arduino.h>
#include "motor.h"
#include "servo.h"
#include "adc.h"
#include "battery_sensor.h"
#include "bluetooth.h"
#include "ultrasonic_sensor.h"
#include "ir_sensor.h"

void demo_omniwheels()
{
  /* variables */
  static int x_joy = 0, y_joy = 0;

  static char sign = 1;
  static int left_up_mot = 0, left_up_sense = 0;
  static int left_down_mot = 0, left_down_sense = 0;
  static int right_up_mot = 0, right_up_sense = 0;
  static int right_down_mot = 0, right_down_sense = 0;

  static int o_left_up_mot = 0;
  static int o_left_down_mot = 0;
  static int o_right_up_mot = 0;
  static int o_right_down_mot = 0;

  /* read data bluetooth */
  update_bluetooth();

  /* resize x_joy and y_joy */
  x_joy = 2 * (data_cmd.joy_x - 127) - 1;
  y_joy = 2 * (data_cmd.joy_y - 127) - 1;

  x_joy = (x_joy >= -1 && x_joy <= 1) ? 0 : -x_joy; 
  y_joy = (y_joy >= -1 && y_joy <= 1) ? 0 : y_joy; 

  /* compute intensity command */
  left_up_mot = y_joy - x_joy;
  right_up_mot = y_joy + x_joy;
  left_down_mot = y_joy + x_joy;
  right_down_mot = y_joy - x_joy;

  /*deduce senses */
  left_up_sense = left_up_mot >= 0 ? 1 : 0;
  right_up_sense = right_up_mot >= 0 ? 0 : 1;
  left_down_sense = left_down_mot >= 0 ? 1 : 0;
  right_down_sense = right_down_mot >= 0 ? 0 : 1;

  if(o_left_up_mot != left_up_mot)
  {
    o_left_up_mot = left_up_mot;
    Serial.print(right_down_mot);
    Serial.print(",");
    Serial.println(right_down_sense);
  }

  /* compute pwm command */
  left_up_mot = abs(left_up_mot);
  right_up_mot = abs(right_up_mot);
  left_down_mot = abs(left_down_mot);
  right_down_mot = abs(right_down_mot);

  left_up_mot = left_up_mot > 255 ? 255 : left_up_mot;
  right_up_mot = right_up_mot > 255 ? 255 : right_up_mot;
  left_down_mot = left_down_mot > 255 ? 255 : left_down_mot;
  right_down_mot = right_down_mot > 255 ? 255 : right_down_mot;

  /* write motors */
  write_pwm_motor(0, right_up_mot, right_up_sense);
  write_pwm_motor(1, left_up_mot, left_up_sense);
  write_pwm_motor(2, right_down_mot, right_down_sense);
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
  demo_omniwheels();
}