#include "engines.h"
#include "encoder.h"
//#include <MemoryFree.h>
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
  actuate_left_vel(0);
  actuate_right_vel(0);

}

void loop() {
  if (Serial.available() > 0){
    String command = read_command();
    Serial.println(command_handler(command));
  }
}
