#ifndef GUARD
#define GUARD
#include <Time.h>
#define DIR1 0
#define STEP1 1
#define ENS1 2
#define FAN 3
#define DIR2 4
#define STEP2 5
#define ENS2 6
#define LS2 7
#define LS4 8
#define LS6 9
#define W_SS 10
#define W_MOSI 11
#define W_MISO 12
#define W_SCK 13
#define DIRB 14
#define DIRA 15
#define LEDS 16
#define POT4 A3
#define POT3 A4
#define POT2 A5
#define POT1 A6
#define SW2 21
#define SERVO 22
#define LIGHT 23
#define LS1 24
#define PWMB 25
#define LS3 26
#define LS5 27
#define S_RESET 28
#define S_DCLK 29
#define S_DIN 30
#define S_BUSY 31
#define PWMA 32
#define PIR A10
#define SW1 A11
#define TEMP A14

struct DCMotor constructDCMotor(int, int , int , int , int , int , int ,  void (*)());
struct DCMotor calibrate(struct DCMotor);
bool PIRRead(void);
void setupPins();
void refreshWatchDog();
void setupWatchDog();
float stdDev(float[], float, int);
float mean(float[], int);
float returnTemperature();
void setupClock();
time_t getTeensy3Time();
time_t timeDelta(time_t, time_t);



struct DCMotor {
  int rampUp;
  int rampDn;
  float speedPer;
  int desiredPos;
  int dir;
  volatile int rampUpCounter = 0;
  volatile int rampDnCounter = 0;
  int errorVal = 0;
  int upperLim;
  int lowerLim;
  int PotPin;
  int DirPin;
  int PwmPin;
  int LSUpperPin;
  int LSLowerPin;
  int expectedTop;
  int expectedBottom;
  void (*refresh)();
  int flag;
};


class CoolingFan {
public:
  bool isOn;
  char mode;
  void autoRegulate(void);
private:
  int controlPin;
  int temperaturePin;
};




#endif

