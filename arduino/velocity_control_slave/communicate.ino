String read_command() {
  int incomingByte = 0;
  String message = "";
  char incoming_char = 'a';

  while (Serial.available() > 0) {
    
    incoming_char = Serial.read();
    if (!(incoming_char == '\r' || incoming_char == '\n')) {
      delay(1);
      message += incoming_char;
    }
  }
  //Serial.flush();
  return message;
}

String command_handler(String command){
  if (command == "report_left"){
    int res = report_left();
    return String(res);
    }
    
  if (command == "report_right"){
    return String(report_right());
    }
    
    
  if(command.substring(0,9)=="left_vel:"){
    String vel = command.substring(9);
    int vel_int = vel.toInt();
    actuate_left_vel(vel_int);
    return "done";
  }

  if(command.substring(0,10)=="right_vel:"){
    String vel = command.substring(10);
    int vel_int = vel.toInt();
    actuate_right_vel(vel_int);
    return "done";
  }
  
}
