#include "lowlevel/theyseemerolling.h"
#include "lowlevel/clock.h"
#include "lowlevel/debug.h"
#include "lowlevel/motors.h"

#include "asservissement/odometry.h"
#include "asservissement/pid.h"

#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/rcc.h>

int main() {
  float voltage_A=0,
        voltage_B=0,
        voltage_sum=0,
        voltage_diff=0; // motor control variables
  int sum_goal=0, diff_goal=0;

  PID_DATA pid_sum = (PID_DATA) {.Te = 0.01,
                        .Kp = 0.0,//0.001,
                        .Ki = 0.00,
                        .Kd = 0.000,
                        .max_eps = 100000000,
                        .position_tolerance = 100};
  pid_init(&pid_sum);

  PID_DATA pid_diff = (PID_DATA) {.Te = 0.01,
                         .Kp = 0.0005,
                         .Ki = 0.000,
                         .Kd = 0.000,
                         .max_eps = 350,
                         .position_tolerance = 100};
  pid_init(&pid_diff);

  clock_setup();
  gpio_setup();
  debug_setup();
  motors_setup();
  odometry_setup();
  odometry odom;
  odometry_get_position();

  while(1)
  {
    odom = odometry_get_position();

    print_odometry(&odom);

    voltage_sum = pid(&pid_sum, sum_goal - 0.5 * (odom.left_total_count + odom.right_total_count));
    voltage_diff = pid(
      &pid_diff,
      diff_goal - (odom.right_total_count - odom.left_total_count)
    );

    voltage_A = voltage_sum + voltage_diff;
    voltage_B = voltage_sum - voltage_diff;

    motor_a_set(voltage_A);
    motor_b_set(voltage_B);
    delay_ms(pid_sum.Te);
  }

  return 0;
}
