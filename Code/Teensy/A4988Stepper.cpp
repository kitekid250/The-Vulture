#include "A4988Stepper.h"
#include "arduino.h"



Stepper::Stepper(int enable, int step, int dir, int limitSwitch, int potentiometer, void (*wDg)()){
  ENPin = enable;
  StepPin = step;
  DirPin = dir;
  LimitSwitchPin = limitSwitch;
  PotPin = potentiometer;
  refresh = wDg;

}

void Stepper::enable(){
  digitalWrite(ENPin, LOW);
}
void Stepper::disable(){
  digitalWrite(ENPin, HIGH); 
}

void Stepper::setDir(int dir){
  if (dir == 1){
    digitalWrite(DirPin, HIGH);
    direction = 1;
  }

  else if (dir == -1){
    digitalWrite(DirPin, LOW);
    direction = -1;

  }
}

void Stepper::toggleDir(){
  if (direction == 1){
    digitalWrite(DirPin, LOW);

  }

  else if (direction == -1){
    digitalWrite(DirPin, HIGH);


  }
}

int Stepper::getPosition(){
  return counter;
}

void Stepper::step(int aDelay){
  //Go through the stepping
  digitalWrite(StepPin, HIGH);
  delay(aDelay);
  digitalWrite(StepPin, LOW);
  delay(aDelay);
  //Increment the counter
  if (direction == -1){
    counter += -1;
  }
  else if (direction == 1){
    counter ++;
  }
}

void Stepper::calibrate(){
  enable();
  setDir(UP);

  int counter = 0;

  while(digitalRead(LimitSwitchPin) == HIGH){
    step(5);
    counter += 1;

    if (counter > 1000){
      Serial.println("Something is wrong.");
      status = 1;
      return;
    }
  }
  for(int i = 0; i < 50; i ++){
    step(3);
  }
  while(digitalRead(LimitSwitchPin) == LOW){
    step(3);
    step(3);
  }

  upperBound = analogRead(PotPin);
  delay(500);
  
  setDir(DOWN);
  
  for(int i = 0; i < 100; i ++){
    step(3);
  }

  while(digitalRead(LimitSwitchPin) == LOW){
    step(3);
    step(3);
  }

  lowerBound = analogRead(PotPin);
  
  setDir(UP);
  
  for (int i = 0; i < 20; i ++){
   step(2);
    step(2);
  }

  Serial.println(upperBound);
  Serial.println(lowerBound);

  disable();


}


