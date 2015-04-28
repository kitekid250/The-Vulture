#include <Stepper.h>

Stepper stepperB(100,9,10);  
Stepper stepperA(100,11,12);  

void setup() {                
  pinMode(13, OUTPUT);     
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);

  digitalWrite(13, LOW);
  digitalWrite(9, LOW);
  digitalWrite(10, LOW);
  digitalWrite(11, LOW);
  digitalWrite(12, LOW);

  stepperA.setSpeed(60);
  stepperB.setSpeed(60);
}

void loop() {
  stepperA.step(100);
  delay(1000);                 
  stepperB.step(100);
  delay(1000);                 
  digitalWrite(13, HIGH);   // sync steppers
  stepperA.step(100);
  digitalWrite(13, LOW);   // unsync steppers
  delay(1000);
}



