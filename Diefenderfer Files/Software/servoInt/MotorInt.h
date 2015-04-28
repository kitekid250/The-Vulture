#ifndef MotorInt_h
#define MotorInt_h

#include "Arduino.h"
#include <CustomStepper.h>

// motor number definitions
#define WINGS 0
#define NECK 1
#define LEFT 2
#define RIGHT 3
#define NUM_MOTORS 4

// Wings Pin Definitions
#define WINGS_DIR 2
#define WINGS_PWM 3
#define WINGS_POT A0

// Neck Pin Definitions
#define NECK_DIR 4
#define NECK_PWM 5
#define NECK_POT A1

// Wing Stepper Definitions
#define STEPPER_EN      8
#define RIGHT_1_STEPPER 9
#define RIGHT_2_STEPPER 10
#define LEFT_1_STEPPER  11
#define LEFT_2_STEPPER  12
#define STEPPER_SYNC    13
#define RIGHT_POT    A3
#define LEFT_POT     A4

// Other Definitions
#define HALT_THRESHOLD 3
#define RUN_THRESHOLD 45
#define MAX_SPEED 128

class MotorInt
{
private:

public:
  MotorInt();
  void updateMotors();
  void setMotor(int motor, int pos);
};

#endif /* MotorInt.h */

