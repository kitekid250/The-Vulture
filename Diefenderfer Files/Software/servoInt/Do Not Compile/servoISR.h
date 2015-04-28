#ifndef servoISR_h
#define servoISR_h

#define WINGS 0
#define NECK 1
#define LEFT 2
#define RIGHT 3
#define NUM_MOTORS 2

#include "Arduino.h"

class servoISR
{
private:

public:
  servoISR(int, int, int, int);
  void updateMotor(int);
};

#endif
