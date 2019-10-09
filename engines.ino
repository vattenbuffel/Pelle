#include "engines.h"
//Update/fix these

/*
  void turnRight(int speedLeft, int speedRight) {
  analogWrite(vac->engine[leftEngine].forwardPin, map(speedLeft, 0, 100, 0, 255));
  analogWrite(vac->engine[rightEngine].backwardPin, map(speedRight, 0, 100, 0, 255));
  }

  void turnLeft(int speedLeft, int speedRight) {
  analogWrite(vac->engine[leftEngine].backwardPin, map(speedLeft, 0, 100, 0, 255));
  analogWrite(vac->engine[rightEngine].forwardPin, map(speedRight, 0, 100, 0, 255));
  }
*/

//Move forward
void moveFor(double ref_speed_left, double ref_speed_right) {
  double cur_speed_left = 0;
  double cur_speed_right = 0;
  long t_old = millis();
  long t_cur = millis();
  int kp = 1;
  int ki = 1;
  int kd = 0.5;
  double e_cur_left = 0;
  double e_cur_right = 0;
  double e_old_left = 0;
  double e_old_right = 0;
  double I_left = 0;
  double I_right = 0;
  double P = 0;
  double D = 0;
  double radius = 0.025;
  
  while(true){
    t_cur = millis();

    //Left
    double passed_left = countLeft;
    countLeft = 0;
    double t_passed = t_cur-t_old;
    t_passed /= 1000;
     
    cur_speed_left = (passed_left/(2*left_encoder_a.segments) * 3.14*2*radius)/(t_passed);
    e_cur_left = ref_speed_left - cur_speed_left;
    
    P = e_cur_left * kp;
    if (isnan(I_left)){I_left = 0;} 
    I_left += e_cur_left;
    D = (e_cur_left-e_old_left)/t_passed * kd;
    
    double PID_left = P + I_left*ki +D; 
    analogWrite(left_engine.forwardPin, map(PID_left*1000, 0, 0.15*1000, 0, 255));


    //Right
    double passed_right = countRight;
    countRight = 0;
   
    cur_speed_right = (passed_right/(2*right_encoder_a.segments) * 3.14*2*radius)/(t_passed);
    e_cur_right = ref_speed_right - cur_speed_right;
    
    P = e_cur_right * kp;
    if (isnan(I_right)){I_right = 0;} 
    I_right += e_cur_right;
    D = (e_cur_right-e_old_right)/t_passed * kd;
    
    double PID_right = P + I_right*ki +D; 
    analogWrite(right_engine.forwardPin, map(PID_right*1000, 0, 0.15*1000, 0, 255));
    
    
    t_old = t_cur;
    e_old_left = e_cur_left;
    e_old_right = e_cur_right;  
    delayMillis(50);
    
    Serial.println(cur_speed_left);
    Serial.print(F("Sum error left: "));
    Serial.println(I_left);
  }
}



/*
  //Moves backward
  void moveBack(int speedLeft, int speedRight) {
  analogWrite(vac->engine[leftEngine].backwardPin, map(speedLeft, 0, 100, 0, 255));
  analogWrite(vac->engine[rightEngine].backwardPin, map(speedRight, 0, 100, 0, 255));
  }
*/
//Stop moving
/*
  void moveStop() {
  analogWrite(vac->engine[leftEngine].forwardPin, 0);
  analogWrite(vac->engine[leftEngine].backwardPin, 0);
  analogWrite(vac->engine[rightEngine].forwardPin, 0);
  analogWrite(vac->engine[rightEngine].backwardPin, 0);
  }
*/
