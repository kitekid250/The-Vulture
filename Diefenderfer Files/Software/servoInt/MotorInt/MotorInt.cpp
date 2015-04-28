#include "MotorInt.h"

byte curPos[NUM_MOTORS];
byte finalPos[NUM_MOTORS];
boolean dir[NUM_MOTORS];
boolean moveDone[NUM_MOTORS];

CustomStepper left(LEFT_1_STEPPER, LEFT_2_STEPPER, (byte[]){
  4, B10, B11, B01, B00}
, 100, 15, CW);

CustomStepper right(RIGHT_1_STEPPER, RIGHT_2_STEPPER, (byte[]){
  4, B10, B11, B01, B00}
, 100, 15, CW);

MotorInt::MotorInt(){
  pinMode(WINGS_POT, INPUT);
  pinMode(NECK_POT, INPUT);
  pinMode(WINGS_DIR, OUTPUT);
  pinMode(WINGS_PWM, OUTPUT);
  pinMode(NECK_DIR, OUTPUT);
  pinMode(NECK_PWM, OUTPUT);

  pinMode(RIGHT_POT, INPUT);
  pinMode(LEFT_POT, INPUT);
  pinMode(STEPPER_EN, OUTPUT);
  pinMode(STEPPER_SYNC, OUTPUT);

  digitalWrite(STEPPER_SYNC, LOW);

  digitalWrite(WINGS_DIR, LOW);
  digitalWrite(WINGS_PWM, LOW);
  digitalWrite(NECK_DIR, LOW);
  digitalWrite(NECK_PWM, LOW);

  finalPos[0] = 70;
  finalPos[1] = 165;
  finalPos[2] = 200;
  finalPos[3] = 120;

  right.rotate();
  left.rotate();

  // don't touch this
  ADMUX |= 0x60;   // prep ADC MUX
  ADMUX &= 0xf0;   // clear MUX channel
  ADCSRA |= 0xCF;  // prep ADC settings and start ADC
  sei();  // enable global interrupts
}

void MotorInt::setMotor(int motor, int pos){
  // easter egg, poll for position of motor
  if (pos == 500){
    Serial.print("Motor: ");
    Serial.print(motor);
    Serial.print(" is at: ");
    Serial.println(curPos[motor]);
  } 
  else {
    finalPos[motor] = pos;
    moveDone[motor] = false;
  }
}

void MotorInt::updateMotors(){

  /*
  Serial.print(curPos[0]);
   Serial.print(", ");
   Serial.println(curPos[1]);
   */

  boolean DltP = false;
  int speedOffset;

  // WINGS ===========================================================
  DltP = finalPos[0] < curPos[0];
  if (!DltP){
    digitalWrite(WINGS_DIR, LOW);
    dir[0] = false;
    speedOffset = 40;
  }
  else{
    digitalWrite(WINGS_DIR, HIGH);
    dir[0] = true;
    speedOffset = 70;
  }
  int absDist = abs(finalPos[0] - curPos[0]);
  if ((dir[0] ^ DltP) || moveDone[0]){   // check for motor overshoot
    analogWrite(WINGS_PWM, 0); // halt
    moveDone[0] = true;
  }
  else {
    if (absDist <= HALT_THRESHOLD){         // check within threshold
      analogWrite(WINGS_PWM, 0);  // stop motor
      moveDone[0] = true;
    }
    else if (absDist < RUN_THRESHOLD)
    {
      absDist = (absDist << 1) + speedOffset;
      analogWrite(WINGS_PWM, absDist);
    }
    else 
      analogWrite(WINGS_PWM, MAX_SPEED); 
  }
  // WINGS ===========================================================

  // NECK ===========================================================
  DltP = finalPos[1] < curPos[1];
  if (!DltP){
    digitalWrite(NECK_DIR, LOW);
    dir[1] = false;
    speedOffset = 30;
  }
  else{
    digitalWrite(NECK_DIR, HIGH);
    dir[1] = true;
    speedOffset = 40;
  }
  absDist = abs(finalPos[1] - curPos[1]);
  if ((dir[1] ^ DltP) || moveDone[1]){   // check for motor overshoot
    analogWrite(NECK_PWM, 0); // halt
    moveDone[1] = true;
  } 
  else {
    if (absDist <= HALT_THRESHOLD){         // check within threshold
      analogWrite(NECK_PWM, 0);  // stop motor
      moveDone[1] = true;
    }
    else if (absDist < RUN_THRESHOLD)
    {
      absDist = (absDist << 1) + speedOffset;
      analogWrite(NECK_PWM, absDist);
    }
    else 
      analogWrite(NECK_PWM, MAX_SPEED);
  }
  // NECK ===========================================================

  // LEFT ==========================================================
  volatile int diff = finalPos[2] - curPos[2];
  delay(9);
  if(abs(diff) > 10){
    digitalWrite(STEPPER_EN, HIGH);
    left.rotate();
    if(signbit(diff))    
      left.setDirection(CCW);
    else 
      left.setDirection(CW);
  }  
  else{
    left.setDirection(STOP);
    digitalWrite(STEPPER_EN, LOW);    
  }
  // Serial.println("Enter Left");
  left.run();
  // LEFT ========================================================== 

  // RIGHT ==========================================================
  diff = finalPos[3] - curPos[3];
  
  // Serial.print(curPos[3]);
  // Serial.print(", ");
  // Serial.println(diff);
  
  if(abs(diff) > 10){
    digitalWrite(STEPPER_EN, HIGH);
    right.rotate();
    if(signbit(diff))    
      right.setDirection(CW);
    else 
      right.setDirection(CCW);
  }  
  else{
    right.setDirection(STOP);
    digitalWrite(STEPPER_EN, LOW);    
  }
  // Serial.println("Enter RIGHT");
  right.run();
  // Serial.println("Exit Right");
  // RIGHT ==========================================================  
}

ISR(ADC_vect) {
  byte channel = ADMUX & 0x0f;   // get current channel
  curPos[channel] = ADCH;
  // ADMUX = ADMUX ^ 1;   // set MUX channel
  ADMUX &= 0xf0;
  ADMUX |= (channel + 1) % NUM_MOTORS;   // set MUX channel
  ADCSRA |= 0x40; // start ADC
};








