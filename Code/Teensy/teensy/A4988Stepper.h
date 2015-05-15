#ifndef GUARD1
#define GUARD1

#define UP 1
#define DOWN -1

void neckMovement(int desiredPosition, float speedPercent, bool homing = false);

class Stepper
{
public:
  //Constructor
  Stepper(int, int, int, int, int, void(*)());
  void setDir(int);
  void enable();
  void disable();
  void calibrate();
  void step(int);
  void test();
  int  getPosition();
  void toggleDir();

  int counter;
  int direction;
  int status;
  int upperBound;
  int lowerBound;
  void (*refresh)();
  void (*asyncFunc)();
  int PotPin;
  int DesiredPosition;
  int RampUp;
  int RampDn;
  int DirPin;
    int StepPin;

private:
  int ENPin;


  int LimitSwitchPin;
  
};

#endif

