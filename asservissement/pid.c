#include "pid.h"

#include <math.h>
#include <stdlib.h>

#ifndef max
	#define max( a, b ) ( ((a) > (b)) ? (a) : (b) )
#endif
#ifndef min
	#define min( a, b ) ( ((a) < (b)) ? (a) : (b) )
#endif

void pid_init(PID_DATA *pid)
{
  pid->prev_eps=0;
  pid->integral=0;
}

double pid(PID_DATA *pid, int eps)
{
  eps = min(eps,  pid->max_eps);
  eps = max(eps, -pid->max_eps);

  pid->integral += pid->Te * eps;
  double output =
      pid->Kp * eps
    + pid->Ki * pid->integral
    + pid->Kd * (eps - pid->prev_eps) / pid->Te;

  pid->prev_eps = eps;
  return output;
}

int reached(PID_DATA *pid, int eps)
{
  if(abs(eps)<pid->position_tolerance)
    // && (abs(eps-pid->prev_eps))/pid->Te<pid->speed_tolerance)
    return 1;
  return 0;
}
