#include "theyseemerolling.h"

#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/timer.h>


void encoders_setup() {
  rcc_periph_clock_enable(RCC_GPIOA);

  // Encoder 1
  rcc_periph_clock_enable(RCC_TIM1);
  gpio_mode_setup(GPIOA, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO8 | GPIO9);
  gpio_set_af(GPIOA, GPIO_AF6, GPIO8 | GPIO9);

  timer_set_period(TIM1, 1024);
  timer_slave_set_mode(TIM1, TIM_SMCR_SMS_EM3);
  timer_ic_set_input(TIM1, TIM_IC1, TIM_IC_IN_TI1);
  timer_ic_set_input(TIM1, TIM_IC2, TIM_IC_IN_TI2);
  timer_enable_counter(TIM1);

  // Encoder 2
  rcc_periph_clock_enable(RCC_TIM2);
  gpio_mode_setup(GPIOA, GPIO_MODE_AF, GPIO_PUPD_NONE, GPIO1 | GPIO0);
  gpio_set_af(GPIOA, GPIO_AF6, GPIO1 | GPIO0);

  timer_set_period(TIM2, 1024);
  timer_slave_set_mode(TIM2, TIM_SMCR_SMS_EM3);
  timer_ic_set_input(TIM2, TIM_IC2, TIM_IC_IN_TI1);
  timer_ic_set_input(TIM2, TIM_IC1, TIM_IC_IN_TI2);
  timer_enable_counter(TIM2);
}

void encoders_reset_tics() {
  timer_set_counter(TIM1, 0);
  timer_set_counter(TIM2, 0);
}

int32_t encoder_1_get_tics() {
  return timer_get_counter(TIM1);
}

int32_t encoder_2_get_tics() {
  return timer_get_counter(TIM2);
}
