void inits(){
  Serial.begin(115200);
  #define leftEncoderA 0
  #define leftEncoderB 1
  #define rightEncoderA 2
  #define rightEncoderB 3
  #define leftEngine 0 
  #define rightEngine 1
  #define startPin 49
  stop = false;

  


  //Encoder init
  
  right_encoder_a = {
    18,
    18,
    1048,
    interruptFunRight,
    initEncoder    
  };
  right_encoder_a.init(&right_encoder_a);
  
  right_encoder_b = {
    19,
    19,
    1048,
    interruptFunRight,
    initEncoder    
  };
  right_encoder_b.init(&right_encoder_b);

  left_encoder_a = {
    21,
    21,
    1048,
    interruptFunLeft,
    initEncoder
  };
  left_encoder_a.init(&left_encoder_a);


  left_encoder_b = {
    20,
    20,
    1048,
    interruptFunLeft,
    initEncoder
  };
  left_encoder_b.init(&left_encoder_b);


  //Engine init
  right_engine = {
    9,
    10,
    0.17*1000
  };

  left_engine = {
    8,
    12,
    0.17*1000
  };




  

  //Pin inits
  pinMode(startPin, INPUT);
  pinMode(left_engine.forwardPin, OUTPUT);
  pinMode(left_engine.backwardPin, OUTPUT);
  pinMode(right_engine.forwardPin, OUTPUT);
  pinMode(right_engine.backwardPin, OUTPUT);

}
