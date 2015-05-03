#include <Servo.h>
#include <Time.h>
#include "vultureWard.h"
#include "A4988Stepper.h"
#include <Adafruit_NeoPixel.h>
#include <Wtv020sd16p.h>
//#include <avr/io.h>
//#include <avr/interrupt.h>



Wtv020sd16p sound(S_RESET,S_DCLK,S_DIN,S_BUSY);
Stepper leftStepper (ENS2, STEP2, DIR2, LS2, POT2, refreshWatchDog);
Stepper rightStepper(ENS1, STEP1, DIR1, LS1, POT1, refreshWatchDog);
struct DCMotor wings;
struct DCMotor neck;
Servo beak;
IntervalTimer neckTimer;
IntervalTimer wingsTimer;
IntervalTimer leftStepperTimer;
IntervalTimer rightStepperTimer;

//NeoPixel Class and Color Setup//
//NOTE: I made an addition to the NeoPixel Class, I added strip.show() to setPixelColor to remove one more call
Adafruit_NeoPixel strip = Adafruit_NeoPixel(5, LEDS, NEO_RGB + NEO_KHZ800);
uint32_t goodGreen = strip.Color(0, 75, 0);
uint32_t warningYellow = strip.Color(75, 75, 0);
uint32_t badRed = strip.Color(75, 0 , 0);
uint32_t neutralBlue = strip.Color(0, 0, 75);

//To call it use strip.setPixelColor(LED # (zero indexed), Defined color above (ie badRed));

///////Global variables//////////
bool occupancyarray[120];   //All initialized as true
size_t occupancyarraySize = 120;
time_t timeLast3 = 0;  //time since last big motion
time_t timeLast2 = 0;  //time since last big motion
time_t timeLast1 = 0;  //time since last big motion
time_t timePIR = 0;     //time since last pir reading

boolean DEBUG = false;
boolean homing = false;
int cycles = 0;


void setup(){
  //0 lights green
  setupClock();
  int beginTime = now();
  setupStrip();
  digitalWrite(FAN, HIGH);
  Serial.begin(115200);

  //1 light green
  strip.setPixelColor(0, goodGreen);
  setupPins();
  neck = constructDCMotor(POT3, PWMB, DIRB, LS4, LS3, 364, 509,  refreshWatchDog);
  wings = constructDCMotor(POT4, PWMA, DIRA, LS6, LS5, 730, 1000, refreshWatchDog);
  beak.attach(SERVO, 600, 2400);
  digitalWrite(FAN, HIGH);

  //2 lights green
  strip.setPixelColor(1, goodGreen);
  setupOccupancyArray();
  sound.reset();
  sound.asyncPlayVoice(2);
  rightStepper.calibrate();                                                                              ///////////ADD ROBUSTNESS to check if it has stalled
  leftStepper.calibrate();                                                                               ///////////ADD ROBUSTNESS to check if it has stalled
  neck = calibrate(neck);
  calibrateWings();

  //3 lights green
  strip.setPixelColor(2, goodGreen);
  neckMovement(475, 0.5); //This is the "Default" neck position
  wingMovementPercent(0.02, 0.5); //This is the "Deualt" wing position
  tipLMovement(0.15, 1);
  tipRMovement(0.15, 1);
  delay(2000);            //Give them time to move
  setupInterrupts();   //Enable the interrupts that protect the actuations

    //4 lights green
  strip.setPixelColor(3, goodGreen);
  moveServo(1.0);
  delay(3000);
  moveServo(0.0); //Closed  
  while (now() - beginTime < 10){    ///This is the warmup time for the PIR Sensor
    delay(500);
    if(DEBUG){
      Serial.println(now() - beginTime);
    }
  }

  //5 Lights green
  //setupWatchDog();
  strip.setPixelColor(4, goodGreen);

}


void loop(){
  //if 15 seconds has elapsed, do a PIR reading and push it into the occupancy array
  if (timeDelta(timePIR, now()) > 15){
    addAndShift(readPIR(), occupancyarray, occupancyarraySize);
    timePIR = now();
  }

  //if 30 minutes has elapsed do movemnt 3
  if (timeDelta(timeLast3, now()) > 30 * 60){
    if (roomOccupied(occupancyarray, occupancyarraySize)){
      movement3();
    }
    timeLast3 = 0; 
  }
  //elif 10 minutes has elapsed do movement 2
  else if (timeDelta(timeLast2, now()) > 10 * 60){
    if (roomOccupied(occupancyarray, occupancyarraySize)){
      movement2();
      timeLast2 = now();
    }  
  }
  //elif 5 minutes has elapsed, do movement 1
  else if(timeDelta(timeLast1, now()) > 1 * 60){
    if (roomOccupied(occupancyarray, occupancyarraySize)){
      //movement1();
      timeLast1 = now(); 
    }  
  }


  //Used to force a particular motion?
  if (digitalRead(SW2) == HIGH){

  movement1();
  delay(5000);
  movement2();
  delay(5000);
  movement3();
  delay(5000);
  cycles ++;
  Serial.printf("Cycles in:%d\n", cycles);
  }

  //error detection: by looking to see if any error flags have been raised


    delay(700);
    refreshWatchDog();
  
}


//////////////////////////////////////////////////////////////////  Movement Functions   //////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void movement1(){
  //Wings open a bit
  wingMovementPercent(0.25, .65);
  neckMovement(440, 0.5);
  //Go rest
  double startTm = millis();
  moveServo(0.25); //1
  sound.asyncPlayVoice(0);
  while(millis() - startTm < 400){
  }
  moveServo(0.0);
  while(millis() - startTm < 750){
  }
  moveServo(0.25); //2
  while(millis() - startTm < 1250){
  }
  moveServo(0.0);
  while(millis() - startTm < 1750){
  }
  refreshWatchDog();
  wingMovementPercent(0.05, .65);
  moveServo(0.25); //3
  while(millis() - startTm < 2500){
  }
  neckMovement(475, 0.5);
  moveServo(0.0);
  while(millis() - startTm < 3100){
  }
  moveServo(0.25); //4
  while(millis() - startTm < 3300){
  }
  moveServo(800, 0.25, 0.0);
  //This takes us to t = 4100




    //Wings close a bit
}
void movement2(){
  wingMovementPercent(0.5, .55);
  delay(100);
  moveServo(0.25);
  sound.asyncPlayVoice(1);
  int startTm = millis();
  neckMovement(400, 0.75);
  while(millis() - startTm < 300){
  }
  moveServo(0.05);
  int st = millis();
  //Move steppers
  //tipRMovement(0.45, 0.5);
  //tipLMovement(0.45, 0.5);
  Serial.print(millis() - st);


  while(millis() - startTm < 800){
  }
  moveServo(0.5);
  while(millis() - startTm < 1100){
  }
  moveServo(0.05);

  //Move steppers
  //tipRMovement(0.2, 0.5);
  //tipLMovement(0.2, 0.5);
  while(millis() - startTm < 1800){
  }
  neckMovement(475, 0.9);
  moveServo(0.6);
  while(millis() - startTm < 2100){
  }
  wingMovementPercent(0.08, .55);

  moveServo(0.05);
  //Move steppers
  while(millis() - startTm < 2500){
  }
  moveServo(0.25);
  while(millis() - startTm < 2700){
  }

  //Move steppers
  moveServo(0);
  //move steppers

}




void movement3(){
  homing = true;
  wingMovementPercent(0.95, 1);
  delay(400);
  tipLMovement(0.8, 0.5);
  tipRMovement(0.8, 0.5);
  delay(200);
  neckMovement(300,1, true);
  Serial.println("Point 1");
  delay(1000);
  double startTm = millis();

  sound.asyncPlayVoice(2);
  while(millis() - startTm < 200){
  } 
  moveServo(1.0);
  refreshWatchDog();

  while(millis() - startTm < 2000){
  }
  moveServo(0.0);
  refreshWatchDog();
  while(millis() - startTm < 3666){
  }
  moveServo(1200, 0.0, 0.9);
  refreshWatchDog();
  moveServo(800, 0.9, 0.0);

  Serial.println("Point 2");


  while(millis() - startTm < 7200){
  }
  moveServo(1000, 0.0, 0.8);
  refreshWatchDog();
  Serial.println("Point 3");

  neckMovement(600, 0.9, true); //Home neck bottom
  Serial.println("Point 4");

  wingMovementPercent(0.4, 1);
  tipLMovement(0.25, 0.5);
  tipRMovement(0.25, 0.5);
  Serial.println("Point 5");
  refreshWatchDog();

  moveServo(1500, 0.8, 0.0);
  delay(5000);
  Serial.println("Point 6");

  neckMovement(475, 0.9);

  homing = false;
    refreshWatchDog();

}



///////////////////////////////////////////////////////////  Servo Functions   /////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void moveServo(float percent){
  const int allOpen = 180;
  const int allClosed = 120;

  int diff = allOpen - allClosed;

  int result = percent * diff;

  beak.write(allOpen - result); //Open
}

void moveServo(int totalTime, float curPercent, float desiredPercent){
  float dif = desiredPercent - curPercent;
  int startTm = millis();
  float lastPush = 9999;

  while(millis() - startTm < totalTime){  //Blocking call
    float pct = 1 - (float((millis() - startTm))/float(totalTime));
    float result = desiredPercent - (dif * pct);
    if ( abs(result - lastPush) > 0.02){
      moveServo(result);
      lastPush = result;
    }
  }

}

/////////////////////////////////////////////////  Occupancy Detection Incl. Analytical Functions    ///////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool roomOccupied(bool occupied[], size_t sizeV){
  ///Analyzes the occupancy array to see if the room is occupied, and it is therefore worth it to do a motion
  if (sizeV == 0){
    return false;
  }
  //Mode 1: 80% occupied in the last 30 minutes
  int longCounter = 0; 
  for (int i = 0; i < sizeV; i++){
    if (occupied[i] == true){
      longCounter ++;
    }
  }

  float inv = 1/float(sizeV);

  if (longCounter * inv > 0.8){
    if(DEBUG){
      Serial.println(longCounter * inv);
    }
    if(DEBUG){
      Serial.println("Mode 1");
    }
    return true;  
  }

  //Mode 2: 50% occupied in the last 5 minutes

  int shortCounter = 0;
  int size2 = sizeV/6;
  for (int n = 0; n < size2; n++){
    if (occupied[n] == true){
      shortCounter ++;
    }

  }


  float inv2 = 1/float(size2);
  if (shortCounter * inv2 > 0.5){
    if(DEBUG){
      Serial.println(shortCounter * inv2);
    }
    if(DEBUG){
      Serial.println("Mode 2");
    }
    return true;
  }  


  return false;
}




boolean readPIR(){
  if (DEBUG){
    Serial.println("Starting to read PIR");
  }
  int value1 = analogRead(PIR);
  int value2 = analogRead(PIR);
  int value3 = analogRead(PIR);
  int value = (value1 + value2 + value3)*0.33;
  if (DEBUG)Serial.print("Value is ");
  if (DEBUG)Serial.println(value);
  if (value < 300){
    return false;
  }
  else {
    return true;
  }

}

void prettyPrint(bool arr[], size_t sizeV){
  Serial.println("Printing Array:");
  Serial.print("[");
  for (int i = 0; i < sizeV; i ++){
    Serial.print(arr[i]);
    Serial.print(",");
  }
  Serial.print("]");
  Serial.println();
}

bool addAndShift(bool value, bool arr[], size_t sizeV){
  ///This function used to add a value to the array, and shift all values right
  ///Efficiency of this can certainlly be improved by not shifting the array, rather using a 32 bit integer and bit shifting

  for (size_t counter = sizeV - 1; counter > 0; counter--){
    arr[counter] = arr[counter - 1];
  }
  arr[0] = value;

  if(DEBUG){
    prettyPrint(arr, sizeV);
  }

}

///////////////////////////////////////////////////////////  Right Tip Asynch Functions    ///////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void tipRMovement(float desiredPercent, float speedPercent){
  if (desiredPercent < 0.0 || desiredPercent > 1){
    return;
  }
  int desiredPosition = rightStepper.lowerBound - (desiredPercent * (rightStepper.lowerBound-rightStepper.upperBound));
  int currentPos = analogRead(rightStepper.PotPin);
  rightStepper.DesiredPosition = desiredPosition;
  rightStepper.RampUp = currentPos + (0.25 * (rightStepper.DesiredPosition - currentPos));
  rightStepper.RampDn = currentPos + (0.75 * (rightStepper.DesiredPosition - currentPos));
  rightStepper.direction = 0;

  //Set the direction
  if ((currentPos - rightStepper.DesiredPosition) < 0){ //Go up
    rightStepper.setDir(DOWN);

  }
  else{                                    //Go down
    rightStepper.setDir(UP);

  }

  int desiredTimerInterval = (speedPercent * (750 - 100)) + 100;
  //Serial.println("Desired Timer Interval");
  //Serial.print(desiredTimerInterval);
  rightStepper.enable();
  rightStepperTimer.begin(asyncrightStepper, 1700);

}

boolean lastTime = false;

void asyncrightStepper(){
  int currentPos = analogRead(rightStepper.PotPin);
  if (rightStepper.direction == -1)
  {
    int randomNum = 3;//random(6);
    //Case1
    if (currentPos > rightStepper.DesiredPosition){
      rightStepperTimer.end();
      rightStepper.disable();
    }

    //Case2
    else if(currentPos > rightStepper.RampDn){
      if(lastTime == false){
        driveR(3);
        lastTime = true;
      }
      else{
        lastTime = false;
      }
    }
    //Case3
    else if(currentPos > rightStepper.RampUp){
      if(randomNum > 1){
        driveR(3);
      }
    }
    else{
      if(lastTime == false){
        driveR(3);
        lastTime = true;
      }
      else{
        lastTime = false;
      }
    }
  }

  else{
    int randomNum = 3; //random(6);
    //Case1
    if (currentPos < rightStepper.DesiredPosition){
      rightStepperTimer.end();
      rightStepper.disable();
    }

    //Case2
    else if(currentPos < rightStepper.RampDn){
      if(lastTime == false){
        driveR(3);
        lastTime = true;
      }
      else{
        lastTime = false;
      }
    }
    //Case3
    else if(currentPos < rightStepper.RampUp){
      if(randomNum > 1){
        driveR(3);
      }
    }
    else{
      if(lastTime == false){
        driveR(3);
        lastTime = true;
      }
      else{
        lastTime = false;
      }
    }
  }

}

void driveR(int microS){
  digitalWrite(rightStepper.StepPin, HIGH);
  delayMicroseconds(microS);
  digitalWrite(rightStepper.StepPin, LOW);
}



///////////////////////////////////////////////////////////  Left Tip Asynch Functions    ///////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void tipLMovement(float desiredPercent, int speedPercent){
  if (desiredPercent < 0.0 || desiredPercent > 1){
    return;
  }
  int desiredPosition = (desiredPercent * (leftStepper.upperBound - leftStepper.lowerBound)) + leftStepper.lowerBound;
  int currentPos = analogRead(leftStepper.PotPin);
  leftStepper.DesiredPosition = desiredPosition;
  leftStepper.RampUp = currentPos + (0.15 * (leftStepper.DesiredPosition - currentPos));
  leftStepper.RampDn = currentPos + (0.85 * (leftStepper.DesiredPosition - currentPos));
  leftStepper.direction = 0;

  //Set the direction
  if ((currentPos - leftStepper.DesiredPosition) > 0){ //Go up
    digitalWrite(leftStepper.DirPin, LOW);
    leftStepper.direction = 1;

  }
  else{                                    //Go down
    digitalWrite(leftStepper.DirPin, HIGH);
    leftStepper.direction = -1;

  }

  int desiredTimerInterval = (speedPercent * (750 - 100)) + 100;
  //  Serial.println("Desired Timer Interval");
  //  Serial.print(desiredTimerInterval);
  leftStepper.enable();
  leftStepperTimer.begin(asyncleftStepper, 1700);

}

void asyncleftStepper(){
  int currentPos = analogRead(leftStepper.PotPin);
  if (leftStepper.direction == -1)
  {
    int randomNum = 3;//random(6);
    //Case1
    if (currentPos > leftStepper.DesiredPosition){
      leftStepperTimer.end();
      leftStepper.disable();
    }

    //Case2
    else if(currentPos > leftStepper.RampDn){
      if(randomNum > 2){
        driveL(3);
      }
    }
    //Case3
    else if(currentPos > leftStepper.RampUp){
      if(randomNum > 1){
        driveL(3);
      }
    }
    else{
      if(randomNum > 2){
        driveL(3);
      }
    }
  }

  else{
    int randomNum = 3; //random(6);
    //Case1
    if (currentPos < leftStepper.DesiredPosition){
      leftStepperTimer.end();
      leftStepper.disable();
    }

    //Case2
    else if(currentPos < leftStepper.RampDn){
      if(randomNum > 2){
        driveL(3);
      }
    }
    //Case3
    else if(currentPos < leftStepper.RampUp){
      if(randomNum > 1){
        driveL(3);
      }
    }
    else{
      if(randomNum > 2){
        driveL(3);
      }
    }
  }

}

void driveL(int microS){
  digitalWrite(leftStepper.StepPin, HIGH);
  delayMicroseconds(microS);
  digitalWrite(leftStepper.StepPin, LOW);
}

/////////////////////////////////////////////////////    Async Neck Functions    //////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void neckMovement(int desiredPosition, float speedPercent, bool homing){
  //Set globals
  if (DEBUG) {
    Serial.println("Neck Movement Begun");
  }
  int currentPos = analogRead(neck.PotPin);
  neck.desiredPos = desiredPosition;
  neck.speedPer = speedPercent;
  neck.rampUp = currentPos + (0.15 * (neck.desiredPos - currentPos));
  neck.rampDn = currentPos + (0.85 * (neck.desiredPos - currentPos));
  neck.dir = 0;
  neck.homing = homing;


  neckTimer.priority(255);

  //Set the direction
  if ((currentPos - neck.desiredPos) > 0){ //Go up
    digitalWrite(neck.DirPin, LOW);
    neck.dir = 1;

  }
  else{                                    //Go down
    digitalWrite(neck.DirPin, HIGH);
    neck.dir = -1;

  }
  if (homing) {
    //Disable interrups
    detachInterrupt(LS3);
    detachInterrupt(LS4);
    while (digitalRead(LS3) && digitalRead(LS4)){
      digitalWrite(neck.PwmPin, HIGH);  //This happens on the final motion, so the neck has to run full speed.  No PWMing needed
    }
    digitalWrite(neck.PwmPin, LOW);  //Turn off the motor

    if (!digitalRead(LS4)){
      neck.upperLim = analogRead(neck.PotPin);
      Serial.println("New Upper Limit Set");
    }
    else if (!digitalRead(LS3)){
      neck.lowerLim = analogRead(neck.PotPin);
      Serial.println("New Lower Limit Set");

    }
    //Back off the switch, ever so slightly
    if (neck.dir == 1){
      digitalWrite(neck.DirPin, HIGH); 
    }
    else{
      digitalWrite(neck.DirPin, LOW); 
    }
    digitalWrite(neck.PwmPin, HIGH);  //Turn off the motor
    delay(50);
    digitalWrite(neck.PwmPin, LOW);  //Turn off the motor

    //reenable interrupts
    attachInterrupt(LS4, ISR_NeckTop, FALLING);
    attachInterrupt(LS3, ISR_NeckBot, FALLING);

  }
  else{
    neckTimer.begin(asyncNeck, 5000);
  }

}

void asyncNeck(){

  int currentPos = analogRead(neck.PotPin);
  int threshold = 5;
  //Add in check for flag, and end if so
  //end
  //clear flags
  if (neck.dir == neck.flag){
    if (DEBUG) {
      Serial.println("Async Flag Triggered");
    }

    analogWrite(neck.PwmPin, 0);
    neckTimer.end();
    neck.flag = 0; 
    return;
  }
  if (currentPos < neck.desiredPos + threshold && currentPos > neck.desiredPos - threshold){  //Base case
    //Turn off motor
    analogWrite(neck.PwmPin, 0);
    //Turn off timer
    //clear flags
    neckTimer.end();
    neck.rampUpCounter = 0;
    neck.rampDnCounter = 0;
    neck.flag = 0;
    if (DEBUG) {
      Serial.println("Basecase Reached");
    }

  }

  else if (((currentPos < neck.rampDn)&&(neck.dir > 0))||((currentPos > neck.rampDn)&&( neck.dir < 0))){  //Ramp down stage
    float drivePct = neck.speedPer - (neck.rampDnCounter * 0.001);
    if (drivePct < 0.5 * neck.speedPer){
      analogWrite(neck.PwmPin, 255 * 0.5 * neck.speedPer);
    }
    else{
      analogWrite(neck.PwmPin, 255 * drivePct);
      neck.rampDnCounter += 1;  
    }

  }
  else if (((currentPos < neck.rampUp)&&(neck.dir > 0))||((currentPos > neck.rampUp)&&( neck.dir < 0))){  //Full speed
    analogWrite(neck.PwmPin,  int(255 * neck.speedPer)); 
  }
  else{  //Ramp up stage

      float drivePct = (neck.rampUpCounter * 0.001) + 0.24;


    if (drivePct > neck.speedPer){
      analogWrite(neck.PwmPin, 255 * neck.speedPer);
    }
    else{
      analogWrite(neck.PwmPin, 255 * drivePct);
      neck.rampUpCounter += 1;  
    }


  }
}


/////////////////////////////////////////////////////    Async Wing Functions    //////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void wingMovementPercent(float desiredPercent, float speedPercent){
  float desiredPosition = (desiredPercent * float(wings.upperLim - wings.lowerLim)) + wings.lowerLim;
  Serial.printf("Desired wing position is: %d\n", int(desiredPosition));
  wingMovement(int(desiredPosition), speedPercent);
}


void wingMovement(int desiredPosition, float speedPercent){
  //Set globals
  int currentPos = analogRead(wings.PotPin);
  wings.desiredPos = desiredPosition;
  wings.speedPer = speedPercent;
  wings.rampUp = currentPos + (0.05 * (wings.desiredPos - currentPos));
  wings.rampDn = currentPos + (0.95 * (wings.desiredPos - currentPos));
  wings.dir = 0;

  wingsTimer.priority(255);

  //Set the direction
  if ((currentPos - wings.desiredPos) > 0){ //Go up
    digitalWrite(wings.DirPin, LOW);
    wings.dir = -1;

  }
  else{                                    //Go down
    digitalWrite(wings.DirPin, HIGH);
    wings.dir = 1;

  }
  wingsTimer.begin(asyncwings, 5000);


}

void asyncwings(){
  int currentPos = analogRead(wings.PotPin);
  int threshold = 5;
  //Add in check for flag, and end if so
  //end
  //clear flags
  if (wings.dir == wings.flag){
    Serial.println("FLAG Raised");
    analogWrite(wings.PwmPin, 0);
    wingsTimer.end();
    wings.flag = 0; 
    return;
  }
  if (currentPos < wings.desiredPos + threshold && currentPos > wings.desiredPos - threshold){  //Base case
    //Turn off motor
    analogWrite(wings.PwmPin, 0);
    //Turn off timer
    //clear flags
    wingsTimer.end();
    wings.rampUpCounter = 0;
    wings.rampDnCounter = 0;
    wings.flag = 0;


  }

  else if (((currentPos < wings.rampDn)&&(wings.dir > 0))||((currentPos > wings.rampDn)&&( wings.dir < 0))){  //Ramp down stage
    float drivePct = wings.speedPer - (wings.rampDnCounter * 0.001);
    if (drivePct < 0.5 * wings.speedPer){
      analogWrite(wings.PwmPin, 255 * 0.5 * wings.speedPer);
    }
    else{
      analogWrite(wings.PwmPin, 255 * drivePct);
      wings.rampDnCounter += 1;  
    }

  }
  else if (((currentPos < wings.rampUp)&&(wings.dir > 0))||((currentPos > wings.rampUp)&&( wings.dir < 0))){  //Full speed

    analogWrite(wings.PwmPin,  int(255 * wings.speedPer)); 
  }
  else{  //Ramp up stage

      float drivePct = (wings.rampUpCounter * 0.001) + 0.24;


    if (drivePct > wings.speedPer){
      analogWrite(wings.PwmPin, 255 * wings.speedPer);
    }
    else{
      analogWrite(wings.PwmPin, 255 * drivePct);
      wings.rampUpCounter += 1;  
    }


  }
}


/////////////////////////////////////////////////////////////////    Wing Calibration   /////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  I wanted to do the neck calibration a bit different considering how finicky the potentiometer is along with the danger involved.  It goes slower.


void calibrateWings(){
  //Find bottom limit
  digitalWrite(DIRA, HIGH);
  while(digitalRead(LS6) == HIGH){
    analogWrite(wings.PwmPin, 100); 
  }
  analogWrite(wings.PwmPin, 0);
  delay(1000);
  wings.upperLim = analogRead(wings.PotPin); 



  //Find top limit
  digitalWrite(DIRA, LOW);
  while(digitalRead(LS5) == HIGH){
    analogWrite(wings.PwmPin, 100); 
  }
  analogWrite(wings.PwmPin, 0);
  delay(1000);
  wings.lowerLim = analogRead(wings.PotPin); 
  Serial.printf("Upper Limit: %d\n", wings.upperLim);
  Serial.printf("Lower Limit: %d\n", wings.lowerLim);

}




/////////////////////////////////////////////////////////////    Actuation Protection ISRS   ////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

boolean setupInterrupts(){
  attachInterrupt(LS1, ISR_TipR, RISING);
  attachInterrupt(LS2, ISR_TipL, RISING);
  attachInterrupt(LS4, ISR_NeckTop, FALLING);
  attachInterrupt(LS3, ISR_NeckBot, FALLING);
  attachInterrupt(LS5, ISR_WingsBot, FALLING);
  attachInterrupt(LS6, ISR_WingsTop, FALLING); 
}

void ISR_NeckTop(){

  Serial.println("Hello2");

  analogWrite(PWMB, 0);
  neck.dir = 1;

  digitalWrite(neck.DirPin, HIGH);
  analogWrite(neck.PwmPin, 120);
  delay(500);
  analogWrite(neck.PwmPin, 0);
  //Raise flag
  neck.flag = neck.dir;
  attachInterrupt(LS4, ISR_NeckTop, FALLING);
}

void ISR_NeckBot(){
  detachInterrupt(LS3);

  Serial.println("Hello1");
  analogWrite(PWMB, 0);
  neck.dir = -1;


  digitalWrite(neck.DirPin, LOW);
  analogWrite(neck.PwmPin, 120);
  delay(500);
  analogWrite(neck.PwmPin, 0);
  //Raise flag
  neck.flag = neck.dir;
  attachInterrupt(LS3, ISR_NeckBot, FALLING);


}

void ISR_TipL(){
  detachInterrupt(LS2);
  leftStepper.disable();
  delay(100);
  leftStepper.toggleDir();
  leftStepper.enable();
  for (int i=0; i < 75; i ++){
    leftStepper.step(2);
  }
  refreshWatchDog();
  leftStepper.disable();
  delay(500);
  leftStepper.toggleDir();
  attachInterrupt(LS2, ISR_TipL, RISING);
}

void ISR_TipR(){
  detachInterrupt(LS1);
  rightStepper.disable();
  delay(100);
  rightStepper.toggleDir();
  rightStepper.enable();
  for (int i=0; i < 75; i ++){
    rightStepper.step(2);
  }
  refreshWatchDog();
  rightStepper.disable();
  delay(500);
  leftStepper.toggleDir();
  attachInterrupt(LS1, ISR_TipR, RISING);
}

void ISR_WingsBot(){
  wings.flag = -1;
  analogWrite(PWMA, 0);
  delay(300);
  digitalWrite(DIRA, HIGH);
  while(digitalRead(LS5) == 0){
    analogWrite(PWMA, 100);
    delay(50);
  } 
  delay(100);
  analogWrite(PWMA, 0);

}

void ISR_WingsTop(){
  wings.flag = 1;
  analogWrite(PWMA, 0);
  delay(300);
  digitalWrite(DIRA, LOW);
  while(digitalRead(LS6) == 0){
    analogWrite(PWMA, 100);
    delay(50);
  } 
  delay(100);
  analogWrite(PWMA, 0);


}

////////////////////////////////////////////// Basic Helper Functions and Trivial Declarations    ////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void setupStrip(){
  for (int i = 0; i < 5; i++){
    strip.setPixelColor(i, neutralBlue);
  }
  strip.begin();
  strip.show(); 
}

void setupOccupancyArray(){
  for (int i = 0; i <120; i++){
    occupancyarray[i] = true;
  }
}

float getTemperatureF(){
  float celcius = analogRead(TEMP) * 3.3 / 1024;
  float fahrenheit = (celcius * 9 / 5) + 32;
  return fahrenheit;
}




