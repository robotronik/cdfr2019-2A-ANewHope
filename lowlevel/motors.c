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
  rcc_periph_clock_enable(RCC_TIM2); // CH4 = PA3_AF1
  rcc_periph_clock_enable(RCC_TIM3); // CH2 = PA7_AF2

  // Enable pins of driver (power on)
  gpio_mode_setup(GPIOA, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE,
    MotorA_Enable | MotorB_Enable
  );
  // IN2 pins of driver (forward/reverse)
  gpio_mode_setup(GPIOA, GPIO_MODE_AF,     GPIO_PUPD_NONE,
    MotorA_Input2 | MotorB_Input2
  );
  // IN1 pins of driver (Speed by PWM)
  gpio_mode_setup(GPIOA, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE,
    MotorA_Input1 | MotorB_Input1
  );
  gpio_set_af    (GPIOA, GPIO_AF1, MotorA_Input1);
  gpio_set_af    (GPIOA, GPIO_AF2, MotorB_Input1);
  gpio_set_output_options(GPIOA, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ,
    MotorA_Input1 | MotorB_Input1
  );

  timer_set_mode              (TIM2,
    TIM_CR1_CKD_CK_INT, TIM_CR1_CMS_EDGE, TIM_CR1_DIR_UP
  );
  timer_set_repetition_counter(TIM2, 0);
  timer_enable_preload        (TIM2);
  timer_continuous_mode       (TIM2);
  timer_set_prescaler         (TIM2, 64);
  timer_set_period            (TIM2, PWM_period);
  timer_enable_oc_output      (TIM2, TIM_OC4);
  timer_set_oc_mode           (TIM2, TIM_OC4, TIM_OCM_PWM2);

  timer_set_mode              (TIM3,
    TIM_CR1_CKD_CK_INT, TIM_CR1_CMS_EDGE, TIM_CR1_DIR_UP
  );
  timer_set_repetition_counter(TIM3, 0);
  timer_enable_preload        (TIM3);
  timer_continuous_mode       (TIM3);
  timer_set_prescaler         (TIM3, 64);
  timer_set_period            (TIM3, PWM_period);
  timer_enable_oc_output      (TIM3, TIM_OC2);
  timer_set_oc_mode           (TIM3, TIM_OC2, TIM_OCM_PWM2);

  // Finally enable the driver
  timer_enable_counter(TIM2);
  timer_enable_counter(TIM3);
  timer_set_oc_value(TIM2, TIM_OC4, 0);
  timer_set_oc_value(TIM3, TIM_OC2, 0);
  gpio_set(GPIOA, MotorA_Enable | MotorB_Enable);
  gpio_set(GPIOA, MotorA_Input2 | MotorB_Input2);
}

// Warning : 0%(forward) and 100%(reverse) have the same PWM value.
// The scale is inverted.

void motor_a_set(int32_t signed_speed) {
  uint32_t value = 0;
  if (signed_speed > 0) {
    value = PWM_period/100 * signed_speed;
    gpio_set(GPIOA, MotorA_Input2);
  } else {
    value = PWM_period/100 * -signed_speed;
    gpio_clear(GPIOA, MotorA_Input2);
  }

  timer_set_oc_value(TIM2, TIM_OC4, value);
}

void motor_b_set(int32_t signed_speed) {
  uint32_t value = 0;
  if (signed_speed > 0) {
    value = PWM_period/100 * signed_speed;
    gpio_set(GPIOA, MotorB_Input2);
  } else {
    value = PWM_period/100 * -signed_speed;
    gpio_clear(GPIOA, MotorB_Input2);
  }

  timer_set_oc_value(TIM3, TIM_OC2, value);
}
