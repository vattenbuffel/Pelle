int incomingByte = 0; // for incoming serial data
String message = "a";
char incoming_char = 'a';

void setup() {
  Serial.begin(115200);
}

void loop() {
  // send data only when you receive data:
  if (Serial.available() > 0) {
    message = "";
    
    while (Serial.available() > 0) {
      incoming_char = Serial.read();
      if (!(incoming_char == '\r' || incoming_char == '\n')){
          //Serial.println("incing message");
          //Serial.print("incoming_char: ");
          //Serial.print(incoming_char);
          delay(1);
          message += incoming_char;
        }

      if(incoming_char == '\r'){
        //Serial.println("cpirövenkuken är == \ r");
      }
      if(incoming_char == '\n'){
        //Serial.println("cpirövenkuken är == \ n");
      }
      
    }
    
    /*
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
      Serial.print("change speeds to: ");
      Serial.print(Serial.parseInt());
      Serial.print(", ");
      Serial.println(Serial.parseInt());
      Serial.print("arduino received: ");
      Serial.println();
      }
    */
    Serial.print("message: ");
    Serial.println(message);
  }

}
