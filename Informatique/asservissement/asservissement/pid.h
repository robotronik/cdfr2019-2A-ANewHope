#pragma once

#include <stdbool.h>

/*
 * Fork of Cdfr2018 @Robotronik
 * You may freely rage with this software
/*/

typedef struct {
 double Te; // Period of the loop TODO determine that inside the script

 double Kp;
 double Ki;
 double Kd;

 int max_eps; // Capping the PID

 // Zone around "zero" where response is zero.
 int position_tolerance;
 double speed_tolerance;

} PID_Configuration;


typedef struct {
  PID_Configuration const* conf;

  double prev_eps;
  double integral;
} PID_Status;

void pid_init(PID_Status *pid, PID_Configuration const* config);
double pid(PID_Status *pid, int eps);
bool reached(PID_Status *pid,int eps);
