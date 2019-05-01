#include "odometry.h"

// WARNING global odometry variable for update during interruption
volatile odometry odometry_internal;
// do not use directly outside odometry.c

void odometry_setup(void)
{
  //gpio_mode_setup(LED_PORT, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, LED_PIN);

  //setup the pooling timer
	rcc_periph_clock_enable(ODOM_RCC_TIM);
	rcc_periph_reset_pulse(ODOM_RST_TIM);
	timer_set_mode(ODOM_TIM, TIM_CR1_CKD_CK_INT,TIM_CR1_CMS_EDGE, TIM_CR1_DIR_UP);
	timer_set_prescaler(ODOM_TIM, ODOM_TIM_PRESCALER);
	timer_disable_preload(ODOM_TIM);
	timer_continuous_mode(ODOM_TIM);
	timer_set_period(ODOM_TIM, ODOM_TIM_PERIOD);
	timer_set_oc_value(ODOM_TIM, TIM_OC1,0);//compare to zero
	timer_enable_counter(ODOM_TIM);

  //start the encoders
  encoder_left_setup();
  encoder_right_setup();

  odometry_internal.x=0;//init the odometry structure
  odometry_internal.y=0;
  odometry_internal.theta=0;
  odometry_internal.left_count=encoder_right_get_counter();
  odometry_internal.right_count=encoder_left_get_counter();

  //start pooling
  nvic_enable_irq(ODOM_NVIC_TIM_IRQ);
	timer_enable_irq(ODOM_TIM, TIM_DIER_CC1IE);
}

void timX_isr(void)
{
  if (timer_get_flag(ODOM_TIM, TIM_SR_CC1IF))
  {
    // Clear compare interrupt flag.
    timer_clear_flag(ODOM_TIM, TIM_SR_CC1IF);

    // first read the encoders, should not be different than -1, 0 or 1
    int dl_l = encoder_left_update (&odometry_internal.left_count);
    int dl_r = encoder_right_update(&odometry_internal.right_count);

    double tmp_delta = ENCODER_STEP_DIST * (dl_l + dl_r)/2;

    // update the position
    odometry_internal.x += tmp_delta * cos(odometry_internal.theta);
    odometry_internal.y += tmp_delta * sin(odometry_internal.theta);
    odometry_internal.theta+=DELTA_L*(dl_l-dl_r);

    //limit robot angle between -PI and PI
    if(odometry_internal.theta > PI)
    {
      odometry_internal.theta += -2*PI;
    }
    else if(odometry_internal.theta < -PI)
    {
      odometry_internal.theta += +2*PI;
    }
  }
}

odometry odometry_get_position(void)
{
  return odometry_internal;
}
