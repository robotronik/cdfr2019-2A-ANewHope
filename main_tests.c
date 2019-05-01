#include "lowlevel/theyseemerolling.h"
#include "lowlevel/clock.h"
#include "lowlevel/eeprom.h"
#include "lowlevel/motors.h"

#include "lowlevel/debug.h"

#include "odometry.h"

void led_blink();
void motor_blink();
void led_blink();
void test_encoders();
void test_direction_general();

int main() {
  // Basic initialization
  clock_setup();
  gpio_setup();

  debug_setup();

  odometry_setup();
  // eeprom_setup();
  motors_setup();

  // uart_send();
  // motor_blink();

  // test_encoders();

  test_direction_general();

  return 0;
}


void led_blink() {
  while(true) {
    led_set_status(0);
    delay_ms(1000);
    led_set_status(1);
    delay_ms(1000);
  }
}

void uart_send() {
  while(true) {
    echo("hello world (sure ?)\n\r");
    led_toggle_status();
    delay_ms(300);
  }
}

void motor_blink() {
  double speed = 0.0;
  while(true) {
    speed = 0;
    motor_b_set(speed);
    motor_a_set(speed);
    led_set_status(0);
    delay_ms(1000);

    speed = 1;
    motor_b_set(speed);
    motor_a_set(speed);
    led_set_status(1);
    delay_ms(1000);

    speed = 0;
    motor_b_set(speed);
    motor_a_set(speed);
    led_set_status(0);
    delay_ms(1000);

    speed = -1;
    motor_b_set(speed);
    motor_a_set(speed);
    led_set_status(1);
    delay_ms(1000);
  }
}

void led_blink_smart() {
  bool status = about_da_power();
  while(true) {
    led_set_status(1);
    delay_ms(100);
    led_set_status(0);
    delay_ms(100);

    if (status)
      led_set_status(1);
    else
      led_set_status(0);
    delay_ms(100);
    led_set_status(0);
    delay_ms(700);
  }
}

void test_encoders() {
  odometry odom;


  while(1)
  {
    odom = odometry_get_position();

    echo_int(odom.left_count);
    echo(" ; ");

    echo_int(odom.right_count);
    echo("\n\r");

    delay_ms(100);
  }
}


void test_direction_general() {
    motor_b_set(1);
    motor_a_set(1);

  odometry odom_old, odom_new;

  odom_old = odometry_get_position();

  while(1)
  {
    odom_old = odom_new;
    odom_new = odometry_get_position();

    if (odom_new.left_count > odom_old.left_count)
      echo(" + ");
    else if (odom_new.left_count < odom_old.left_count)
      echo(" - ");
    else
      echo(" 0 ");

    echo(";");

    if (odom_new.right_count > odom_old.right_count)
      echo(" + ");
    else if (odom_new.right_count < odom_old.right_count)
      echo(" - ");
    else
      echo(" 0 ");

    echo("\n\r");

    delay_ms(300);
  }

}
