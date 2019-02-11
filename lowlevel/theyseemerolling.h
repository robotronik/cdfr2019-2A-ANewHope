#pragma once

#include <stdbool.h>
#include <stdint.h>

// This API should be splitted to specific headers

/*****************************************************************************/
// Led,…
void gpio_setup();

void led_set_status(uint32_t status); // PWM ?
bool about_da_power();

void set_all_1();

/*****************************************************************************/
// SPI-connected EEPROM chip
void eeprom_setup();
// TODO
void* eeprom_read();
void eeprom_write(void* data);

/*****************************************************************************/
void can_setup();
// TODO !
void* can_get_message();
void can_send(void* msg);

/*****************************************************************************/
void motors_setup();
void motor_a_set(int32_t signed_speed);
void motor_b_set(int32_t signed_speed);

/*****************************************************************************/
void adcs_setup();
// Value in ampers ?
uint32_t adc_a_value();
uint32_t adc_b_value();

/*****************************************************************************/
void encoders_setup();
void encoders_reset_tics();
// Should reset internal counters ?
int32_t encoder_a_get_tics();
int32_t encoder_b_get_tics();
