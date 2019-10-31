//Doesn't work with ENCODER.H. No idea why
#ifndef BAJS_H
#define BAJS_H

volatile unsigned long countLeft = 0;
volatile unsigned long countRight = 0;

typedef struct tEncoder {
  int pin;
  int interruptNr;
  int segments;
  void (*interruptFun)();
  void (*init)(struct tEncoder* ENCODER);
} ENCODER, *PENCODER;


#endif
