#include "engines.h"
#include "encoder.h"
#include <MemoryFree.h>
#include <Wire.h> //needed?
#include <math.h>




boolean stop;
ENGINE left_engine;
ENGINE right_engine;
ENCODER left_encoder_a;
ENCODER left_encoder_b;
ENCODER right_encoder_a;
ENCODER right_encoder_b;



void setup() {
  //Initial inits
  inits();
  

  //Test segmenteeeeee
  Serial.println(F("")); 
  Serial.println(F("")); 
  Serial.println(F("TEST"));
 moveFor(0.15, 0.15);
 
  //

 
  
  //Final inits
  delayMillis(250);
  Serial.println(F("START"));
}



void loop() {
}
