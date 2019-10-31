#include "engines.h"

void actuate_left_vel(int vel){
  if(vel > left_engine.v_max) vel = left_engine.v_max;
  analogWrite(left_engine.forwardPin, map(vel, 0, left_engine.v_max, 0, 255));
}
void actuate_right_vel(int vel){
  if(vel > right_engine.v_max) vel = right_engine.v_max;
  analogWrite(right_engine.forwardPin, map(vel, 0, right_engine.v_max, 0, 255));
}

//Implement moving backwards
