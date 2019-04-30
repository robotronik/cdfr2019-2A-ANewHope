#include "pid.h"


void pid_init(PID_DATA *pid)
{
  pid->prev_eps=0;
  pid->integral=0;
}

float pid(PID_DATA *pid, int eps)//TODO: should use systick to measure Te
{
  float output;
  pid->integral=pid->integral+pid->Te*eps;
  output=eps*pid->Kp+pid->Ki*pid->integral+pid->Kd*(eps-pid->prev_eps)/pid->Te;
  pid->prev_eps=eps;
  return output;
}

int reached(PID_DATA *pid,int eps)
{
  if(abs(eps)<pid->position_tolerance)// && (abs(eps-pid->prev_eps))/pid->Te<pid->speed_tolerance)
    return 1;
  return 0;
}
