#include "lowlevel/theyseemerolling.h"
#include "lowlevel/clock.h"
#include "lowlevel/debug.h"
#include "lowlevel/motors.h"

#include "asservissement/odometry.h"
#include "asservissement/pid.h"
#include "asservissement/calibration.h"

void asservissement();

int main() {
  clock_setup();
  gpio_setup();
  // debug_setup();
  // motors_setup();

  // asservissement();

  while (true) {
    delay_ms(1000);
    led_toggle_status();

  };
  return 0;
}


void asservissement() {
  float voltage_A=0,
        voltage_B=0,
        voltage_sum=0,
        voltage_diff=0; // motor control variables
  int sum_goal=0, diff_goal=0;

  PID_Status pid_delta, pid_theta;
  pid_init(&pid_delta, &PID_Configuration_delta);
  pid_init(&pid_theta, &PID_Configuration_theta);


  odometry_setup();
  odometry odom;
  odometry_get_position();

  while(1)
  {
    odom = odometry_get_position();

    print_odometry(&odom);

    voltage_sum = pid(&pid_delta, sum_goal - 0.5 * (odom.left_total_count + odom.right_total_count));
    voltage_diff = pid(
      &pid_theta,
      diff_goal - (odom.right_total_count - odom.left_total_count)
    );

    voltage_A = voltage_sum + voltage_diff;
    voltage_B = voltage_sum - voltage_diff;

    motor_a_set(voltage_A);
    motor_b_set(voltage_B);
    delay_ms(pid_delta.conf->Te);
  }
}
