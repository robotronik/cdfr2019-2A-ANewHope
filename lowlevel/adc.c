#include "theyseemerolling.h"
#include "clock.h"

#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/gpio.h>
#include <libopencm3/stm32/adc.h>
#include <libopencm3/stm32/dma.h>

// ACS711KLCTR-25AB-T
// (55mv/A)

volatile uint16_t adc_res[2];

void adcs_setup() {
  rcc_periph_clock_enable(RCC_GPIOB);
  rcc_periph_clock_enable(RCC_ADC);
  rcc_periph_clock_enable(RCC_DMA1);

  gpio_mode_setup(GPIOB, GPIO_MODE_ANALOG, GPIO_PUPD_NONE, GPIO0);
  gpio_mode_setup(GPIOB, GPIO_MODE_ANALOG, GPIO_PUPD_NONE, GPIO1);

  // DMA Setup

  dma_disable_channel(DMA1, DMA_CHANNEL1);

  dma_enable_circular_mode(DMA1, DMA_CHANNEL1);
  dma_enable_memory_increment_mode(DMA1, DMA_CHANNEL1);

  dma_set_peripheral_size(DMA1, DMA_CHANNEL1, DMA_CCR_PSIZE_16BIT);
  dma_set_memory_size(DMA1, DMA_CHANNEL1, DMA_CCR_MSIZE_16BIT);

  dma_set_read_from_peripheral(DMA1, DMA_CHANNEL1);
  dma_set_peripheral_address(DMA1, DMA_CHANNEL1, ADC_DR(ADC1));

  dma_set_memory_address(DMA1, DMA_CHANNEL1, (uint32_t) &adc_res);
  dma_set_number_of_data(DMA1, DMA_CHANNEL1, 2);

  dma_enable_transfer_complete_interrupt(DMA1, DMA_CHANNEL1);
  dma_enable_channel(DMA1, DMA_CHANNEL1);


  // ADC Setup
  adc_power_off(ADC1);
  adc_set_continuous_conversion_mode(ADC1);
  adc_disable_discontinuous_mode_regular(ADC1);

  // adc_enable_external_trigger_regular(ADC1, )
  adc_set_sample_time_on_all_channels(ADC1, ADC_SMPR_SMP_7DOT5CYC);
  adc_set_right_aligned(ADC1);

  adc_power_on(ADC1);

  delay_ms(1);

  adc_calibrate(ADC1);

  // ADC1_IN1,2 (PB0, PB1)
  uint8_t channel_seq[] = { 1, 2 };
  adc_set_regular_sequence(ADC1, 1, channel_seq);
  adc_set_resolution(ADC1, ADC_CFGR1_RES_12_BIT);

  delay_ms(1);
}

uint32_t adc_a_value() {
  adc_start_conversion_regular(ADC1);
  while (!(adc_eoc(ADC1)));
  // temp=adc_read_regular(ADC1);
  // gpio_port_write(GPIOE, temp << 4);
  // my_usart_print_int(USART2, temp);


  return 0;
}

uint32_t adc_b_value() {
  return 0;
}
