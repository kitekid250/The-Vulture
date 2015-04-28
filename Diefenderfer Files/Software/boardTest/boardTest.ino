#include <Stepper.h>

Stepper a(200, 8, 10);
Stepper b(200, 9, 14);

void setup(){
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(14, OUTPUT);
  a.setSpeed(60);
  b.setSpeed(60);
}

void loop(){
  digitalWrite(6, LOW); // desync
  digitalWrite(7, HIGH);// enable
  a.step(200);
  b.step(200);
  
  digitalWrite(6, HIGH); //sync
  a.step(200);
  b.step(200);
  
  digitalWrite(7,LOW); //disable
  delay(2000);
}
