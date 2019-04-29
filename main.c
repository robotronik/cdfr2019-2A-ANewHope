#include "lowlevel/theyseemerolling.h"
#include "lowlevel/clock.h"

#include "lowlevel/debug.h"
#include "odometry.h"

#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/rcc.h>

#define LED_PORT GPIOA
#define LED_PIN GPIO5

int main() {
  clock_setup();
  //gpio_setup();
  //eeprom_setup();
  //encoders_setup();
  //motors_setup();
  rcc_periph_clock_enable(RCC_GPIOA);
  gpio_mode_setup(LED_PORT, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, LED_PIN);

  debug_setup();
  odometry_setup();
  odometry test_odom;odometry_get_position();

  while(1)
  {
    test_odom=odometry_get_position();
    //gpio_toggle(LED_PORT, LED_PIN);
    echo("blink\n\r");
    echo_int(test_odom.left_count);
    echo("\n\r");
    echo_int(test_odom.right_count);
    echo("\n\r");
    delay_ms(500);
  }

  return 0;
}
