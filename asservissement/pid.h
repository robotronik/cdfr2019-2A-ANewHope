/*
 * Fork of Cdfr2018 @Robotronik
 * You may freely rage with this software
 */
#pragma once


typedef struct{
  double Kp;
  double Ki;
  double Kd;
  int max_eps;

  double prev_eps;
  double integral;
  double Te;
  int position_tolerance;
  double speed_tolerance;
} PID_DATA;

void pid_init(PID_DATA *pid);
double pid(PID_DATA *pid, int eps);
int reached(PID_DATA *pid,int eps);
