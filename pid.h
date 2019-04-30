/*
 * Fork of Cdfr2018 @Robotronik
 * You may freely rage with this software
 */
#pragma once

#include <stdlib.h>

typedef struct{
  float Kp;
  float Ki;
  float Kd;
  float prev_eps;
  float integral;
  float Te;
  int position_tolerance;
  float speed_tolerance;
} PID_DATA;

void pid_init(PID_DATA *pid);
float pid(PID_DATA *pid, int eps);
int reached(PID_DATA *pid,int eps);
