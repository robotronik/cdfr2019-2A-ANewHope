#pragma once

#include <math.h>//LDLIBS+= -lm

#include <libopencm3/cm3/nvic.h>
#include <libopencm3/stm32/rcc.h>
#include <libopencm3/stm32/timer.h>

#define PI 3.14159265359
#include "lowlevel/encoders.h"

#define LED_PORT GPIOA
#define LED_PIN GPIO5

// Robot mechanical caracteristics, dimensions in mm

// distance between encoders
#define ENCODER_DIST 192

// diameter of the encoder wheel
#define ENCODER_WHEEL_D 60.0
// distance for one encoder step
#define ENCODER_STEP_DIST (ENCODER_WHEEL_D * PI / ENCODER_PERIOD)
#define DELTA_L (ENCODER_STEP_DIST / ENCODER_DIST)

//POOLING Timer
#define ODOM_TIM TIM15
// magic trick of timer 15 normaly timX_isr
#define timX_isr(void) tim1_brk_tim15_isr(void)
#define ODOM_RCC_TIM RCC_TIM15
//normaly NVIC_TIMx_IRQ
#define ODOM_NVIC_TIM_IRQ NVIC_TIM1_BRK_TIM15_IRQ
#define ODOM_RST_TIM RST_TIM15
//change these 2 lines to setup interruption frequency
// #define ODOM_TIM_PRESCALER ((rcc_apb1_frequency * 2) / 5000)
#define ODOM_TIM_PRESCALER 50
#define ODOM_TIM_PERIOD 600

typedef struct{//positions in mm and angles in rad
  double x;
  double y;
  double theta;

  int left_count;//last encoders count
  int right_count;
}odometry;

void odometry_setup(void);
odometry odometry_get_position(void);

