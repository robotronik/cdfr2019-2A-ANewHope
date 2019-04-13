#include "theyseemerolling.h"

#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/rcc.h>

// Motor A :
#define MotorA_Enable   GPIO4
#define MotorA_Input1   GPIO3
#define MotorA_Input2   GPIO2

// Motor B :
#define MotorB_Enable   GPIO6
#define MotorB_Input1   GPIO7
#define MotorB_Input2   GPIO5


void motors_setup() {
  rcc_periph_clock_enable(RCC_GPIOA);

  gpio_mode_setup(GPIOA, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, MotorA_Enable);
  gpio_mode_setup(GPIOA, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, MotorB_Enable);

  gpio_mode_setup(GPIOA, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, MotorA_Input1);
  gpio_mode_setup(GPIOA, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, MotorB_Input1);

  gpio_mode_setup(GPIOA, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, MotorA_Input2);
  gpio_mode_setup(GPIOA, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, MotorB_Input2);


  gpio_clear(GPIOA,
      MotorA_Enable
    | MotorB_Enable
    | MotorA_Input1
    | MotorB_Input1
    | MotorA_Input2
    | MotorB_Input2
  );

}

void motor_a_set(int32_t signed_speed) {
  if (signed_speed == 0) {
    gpio_clear(GPIOA, MotorA_Enable);
    return;
  }

  gpio_set  (GPIOA, MotorA_Enable);
  gpio_set  (GPIOA, MotorA_Input1);
  gpio_clear(GPIOA, MotorA_Input2);
}

void motor_b_set(int32_t signed_speed) {
  if (signed_speed == 0) {
    gpio_clear(GPIOA, MotorB_Enable);
    return;
  }

  gpio_set  (GPIOA, MotorB_Enable);
  gpio_set  (GPIOA, MotorB_Input1);
  gpio_clear(GPIOA, MotorB_Input2);
}
