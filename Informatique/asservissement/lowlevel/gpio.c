#include "theyseemerolling.h"

#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>

#define StatusLedRCC  RCC_GPIOA
#define StatusLedPort GPIOA
#define StatusLedPin  GPIO11

void gpio_setup() {
  rcc_periph_clock_enable(StatusLedRCC);

  // status led
  gpio_mode_setup(StatusLedPort, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, StatusLedPin);
  // power input
  // gpio_mode_setup(GPIOF, GPIO_MODE_INPUT, GPIO_PUPD_PULLDOWN, GPIO1);
}

void led_toggle_status() {
  gpio_toggle(StatusLedPort, StatusLedPin);
}

void led_set_status(uint32_t status) {
  if (status == 0)
    gpio_clear(StatusLedPort, StatusLedPin);
  else
    gpio_set  (StatusLedPort, StatusLedPin);
}

bool about_da_power() {
  return (gpio_get(GPIOF, GPIO1) == 0);
}

void set_all_1() {
  rcc_periph_clock_enable(RCC_GPIOA);
  rcc_periph_clock_enable(RCC_GPIOB);
  rcc_periph_clock_enable(RCC_GPIOF);

  uint16_t gpioa_pins = 0
    | GPIO0
    | GPIO1
    | GPIO2
    | GPIO3
    | GPIO4
    | GPIO5
    | GPIO6
    | GPIO7
    | GPIO8
    | GPIO9
    | GPIO10
    | GPIO11
    | GPIO12
    | GPIO13
    | GPIO14;

  uint16_t gpiob_pins = 0
    | GPIO0
    | GPIO1
    // | GPIO2
    | GPIO3
    | GPIO4
    | GPIO5
    | GPIO6
    | GPIO7;

  uint16_t gpioc_pins = 0
    | GPIO0
    | GPIO1;

  gpio_mode_setup(GPIOA, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, gpioa_pins);
  gpio_mode_setup(GPIOB, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, gpiob_pins);
  gpio_mode_setup(GPIOF, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, gpioc_pins);
  gpio_set(GPIOA, gpioa_pins);
  gpio_set(GPIOB, gpiob_pins);
  gpio_set(GPIOF, gpioc_pins);
}
