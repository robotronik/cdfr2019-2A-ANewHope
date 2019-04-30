#include "lowlevel/theyseemerolling.h"
#include "lowlevel/clock.h"
#include "lowlevel/eeprom.h"

int main() {
  clock_setup();
  gpio_setup();
  // eeprom_setup();
  // encoders_setup();
  // motors_setup();


  led_blink();

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

void motor_blink() {
  while(true) {
    motor_b_set(0);
    delay_ms(1000);
    motor_b_set(1);
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
