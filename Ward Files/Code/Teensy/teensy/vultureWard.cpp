#include "vultureWard.h"
#include "arduino.h"
#include <Time.h>


void setupClock(){
  Teensy3Clock.set(0);
  setSyncProvider(getTeensy3Time);
  setSyncInterval(60);

}

time_t getTeensy3Time()
{
  return Teensy3Clock.get();
}


time_t timeDelta(time_t t1, time_t t2){
  //A more robust version of simple subtraction.  It should be able to handle overflows without fail

  if ((t2 - t1) < 86400){
    return t2 - t1;
  }
  else{
    return t2;
  }

}


bool PIRRead(void)
{
  if (digitalRead(PIR) == HIGH){
    return true;
  }
  else{
    return false;
  }
}

void CoolingFan::autoRegulate(){
  //Does what it is supposed to do, depending on the mode.  If temp is too high, then turn on the fan

  //Auto

  //On

  //Off

}

void refreshWatchDog(){
  noInterrupts();
  WDOG_REFRESH = 0xA602;
  WDOG_REFRESH = 0xB480;
  interrupts();

}

void setupWatchDog(){
  noInterrupts();
  WDOG_UNLOCK = WDOG_UNLOCK_SEQ1;
  WDOG_UNLOCK = WDOG_UNLOCK_SEQ2;
  delayMicroseconds(1);
  WDOG_STCTRLH = 0x0001; // Enable WDG
  WDOG_TOVALL = 200*20; // The next 2 lines sets the time-out value. This is the value that the watchdog timer compare itself to.
  WDOG_TOVALH = 0;
  WDOG_PRESC = (1 << 10); // This sets prescale clock so that the watchdog timer ticks at 1kHZ instead of the default 1kHZ/4 = 200 HZ
  interrupts();
  delay(20);


}

float returnTemperature(){
  //Gets values to work with
  int numValues = 6;
  float values[numValues];
  for (int i = 0; i < numValues; i++){
    values[i] = 100 * analogRead(TEMP) * 0.0009765625 * 3.3;
  }
  float theMean = mean(values, numValues);
  //Attempt to identify if the sensor is not working (Symptoms = far too low a value)
  if (theMean < 8.0){
    return 99.0;
  }
  //Atempt to identify if the sensor is not connected (Symptoms = floating values)
  if (stdDev(values, theMean, numValues) > 5){
    return 99.0;
  }

  return theMean;

}


float stdDev(float values[], float theMean, int numValues){
  float sum = 0;
  for (int i = 0; i < numValues; i++){
    sum += (values[i] - theMean) * (values[i] - theMean);
  }

  float toSqr = sum / ( numValues - 1);
  return sqrt(toSqr);
}

float mean(float values[], int numValues){
  float sum = 0;
  for (int i = 0; i < numValues; i++){
    sum += values[i];
  }
  float theMean = sum / numValues;
  return theMean;
}

void setupPins(){
  pinMode(DIR1, OUTPUT);
  pinMode(STEP1, OUTPUT);
  pinMode(ENS1, OUTPUT);
  pinMode(FAN, OUTPUT);
  pinMode(DIR2, OUTPUT);
  pinMode(STEP2, OUTPUT);
  pinMode(ENS2, OUTPUT);
  pinMode(LS1, INPUT);
  pinMode(LS3, INPUT);
  pinMode(LS5, INPUT);
  //SPI Pins not used and not set
  pinMode(DIRB, OUTPUT);
  pinMode(DIRA, OUTPUT);
  pinMode(LEDS, OUTPUT);
  //POT4 A3
  //POT3 A4
  //POT2 A5
  //POT1 A6
  pinMode(SW1, INPUT);
  pinMode(SERVO, OUTPUT);
  //LIGHT 23
  pinMode(LS2, INPUT);
  pinMode(PWMB, OUTPUT);
  pinMode(LS4, INPUT);
  pinMode(LS6, INPUT);
  pinMode(S_RESET, OUTPUT);
  pinMode(S_DCLK, OUTPUT);
  pinMode(S_DIN, OUTPUT);
  pinMode(S_BUSY, INPUT);
  pinMode(PWMA, OUTPUT);
  pinMode(PIR, INPUT); //These are actually analog
  pinMode(SW2, INPUT); //These are actually analog
  pinMode(TEMP, INPUT);

  digitalWrite(ENS1, HIGH);
  digitalWrite(ENS2, HIGH);
  
  analogWriteFrequency(32, 150); //Keeps the wings from stalling
  //analogWriteFrequency(25, 50); //25 is on the same clock, so it takes the value of 100 as well

}


struct DCMotor constructDCMotor(int PotPinin, int PWMPinin, int DIRPinin, int LSUpperPinin, int LSLowerPinin, int expectedTop, int expectedBottom,  void (*wDg)()){
  DCMotor motor;
  motor.PwmPin = PWMPinin;
  motor.DirPin = DIRPinin;
  motor.PotPin = PotPinin;
  motor.LSUpperPin = LSUpperPinin;
  motor.LSLowerPin = LSLowerPinin;
  motor.expectedTop = expectedTop;
  motor.expectedBottom = expectedBottom;
  motor.refresh = wDg;
  motor.flag = 0;
  return motor;
}

struct DCMotor calibrate(struct DCMotor motor){
  //Run to top limit
  digitalWrite(motor.DirPin, LOW);
  while (analogRead(motor.PotPin) > (motor.expectedTop + 20) && digitalRead(motor.LSUpperPin) == true){
    analogWrite(motor.PwmPin, 100);
    delay(20);
  }
  while(digitalRead(motor.LSUpperPin) == true){
    analogWrite(motor.PwmPin, 80);
    delay(10);
  }
  analogWrite(motor.PwmPin, 0);
  motor.upperLim = analogRead(motor.PotPin);
  

  //Run to bottom limit
  digitalWrite(motor.DirPin, HIGH);
  while (analogRead(motor.PotPin) < (motor.expectedBottom - 20) && digitalRead(motor.LSLowerPin) == true){
    analogWrite(motor.PwmPin, 100);
    delay(20);
    motor.refresh();

  }

  while(digitalRead(motor.LSLowerPin) == true){
    analogWrite(motor.PwmPin, 80);
    delay(10);
    motor.refresh();
  }

  analogWrite(motor.PwmPin, 0);

  motor.lowerLim = analogRead(motor.PotPin);
  //Check for potentiometer/motor errors????

  return motor;
}
