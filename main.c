#include "lowlevel/theyseemerolling.h"
#include "lowlevel/clock.h"
#include "lowlevel/debug.h"
#include "lowlevel/motors.h"
#include "odometry.h"
#include "pid.h"

#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/rcc.h>

int main() {
  float voltage_A=0,
        voltage_B=0,
        voltage_sum=0,
        voltage_diff=0; // motor control variables
  int sum_goal=0, diff_goal=0;

  PID_DATA pid_sum = (PID_DATA) {.Te = 0.01,
                        .Kp = 0.01,
                        .Ki = 0.01,
                        .Kd = 0.0001,
                        .position_tolerance = 100};
  pid_init(&pid_sum);
  PID_DATA pid_diff = (PID_DATA) {.Te = 0.01,
                         .Kp = 0.01,
                         .Ki = 0.01,
                         .Kd = 0.0001,
                         .position_tolerance = 100};
  pid_init(&pid_diff);

  clock_setup();
  gpio_setup();
  //debug_setup();
  motors_setup();
  odometry_setup();
  odometry odom;
  odometry_get_position();

  while(1)
  {
    odom=odometry_get_position();
    motor_b_set(-0.5);
    delay_ms(1000);
    motor_b_set(1);
    echo("blink\n\r");
    echo_int(odom.left_count);
    echo("\n\r");
    echo_int(odom.right_count);
    echo("\n\r");
    delay_ms(1000);

    voltage_sum = pid(&pid_sum, sum_goal - 0.5 * (odom.left_count + odom.right_count));
    voltage_diff = pid(&pid_diff, diff_goal - (odom.right_count - odom.left_count));

    voltage_A = voltage_sum + voltage_diff;
    voltage_B = voltage_sum - voltage_diff;

    //motor_a_set(voltage_A);
    //motor_b_set(voltage_B);
    //delay_ms(pid_sum.Te);

  }

  return 0;
}
