//Delays the program but doesn't stop interrupts
void delayMillis(int period) {
  int startTime =  millis();
  while (millis() < startTime + period) {
  }
}

//Why does this not work?
/*
boolean ready() {
    boolean res = false;
    if (digitalRead(startPin) == LOW) {
      res = true;
    }
    return res;
  }
*/
