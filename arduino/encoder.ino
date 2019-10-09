#include "encoder.h"

//Inits the encoder
void initEncoder(PENCODER ENCODER) {
  pinMode(ENCODER->pin, INPUT);
  digitalWrite(ENCODER->pin, HIGH);
  attachInterrupt(digitalPinToInterrupt(ENCODER->interruptNr), ENCODER->interruptFun, CHANGE);
  countLeft = 0; 
  countRight = 0; 
}


//Interruptfunction for left encoder. Updates countleft everytime the encoder passes
void interruptFunLeft(){
  countLeft++;
}

void interruptFunRight(){
  countRight++;
}
