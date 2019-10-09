int incomingByte = 0; // for incoming serial data
char send_left = '1';
char send_right = '2';
char new_speeds = '3';

void setup() {
  Serial.begin(9600); // opens serial port, sets data rate to 9600 bps
}

void loop() {
  // send data only when you receive data:
  if (Serial.available() > 0) {
    // read the incoming byte:
    incomingByte = Serial.read();

    // say what you got:
    
    
    if (incomingByte == send_left){
      Serial.print("I should: ");
      Serial.println("send_left");
    }
    else if (incomingByte == send_right){
      Serial.print("I should: ");
      Serial.println("send_right");
    }
    else if (incomingByte == new_speeds){
      Serial.print("I should: ");
      Serial.println("change speeds to");
      Serial.println(Serial.parseInt());
      Serial.println(Serial.parseInt());
      }
  }
}
