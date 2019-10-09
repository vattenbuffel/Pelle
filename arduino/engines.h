#ifndef ENGINES.H
#define ENGINES.H

typedef struct tEngine {
  int forwardPin, backwardPin;
} ENGINE, *PENGINE;



//void moveOneSquare(PVAC vac);
void moveQuarterLeft();
void moveQuarterRight();
#endif
