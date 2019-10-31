#ifndef ENGINES_H
#define ENGINES_H

typedef struct tEngine {
  int forwardPin, backwardPin;
  double v_max;
} ENGINE, *PENGINE;



//void moveOneSquare(PVAC vac);
void moveQuarterLeft();
void moveQuarterRight();
#endif
