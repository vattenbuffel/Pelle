#include "engines.h"
#include "encoder.h"
#include <MemoryFree.h>
#include <Wire.h> //needed?
#include <math.h>




ENGINE left_engine;
ENGINE right_engine;
ENCODER left_encoder_a;
ENCODER left_encoder_b;
ENCODER right_encoder_a;
ENCODER right_encoder_b;



void setup() {
  //Initial inits
  inits();
}



void loop() {
  
}
