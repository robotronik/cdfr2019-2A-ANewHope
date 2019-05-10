#pragma once

extern const double Pi;

// Robot mechanical caracteristics, dimensions in mm

extern const double Encoders_Axis_Distance;
extern const double Encoders_Wheel_Diameter;
extern const double Encoders_Dist_Per_Step;
extern const double Encoders_Theta_Per_Diff;

// PID Calibration
#include "pid.h"

extern const PID_Configuration
  PID_Configuration_delta,
  PID_Configuration_theta;
