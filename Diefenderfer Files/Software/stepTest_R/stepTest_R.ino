#include <CustomStepper.h>

CustomStepper stepper(9,10, (byte[]){
  4, B10, B11, B01, B00}
, 100, 25, CW);
boolean rotate1 = false;
boolean rotatedeg = false;
boolean crotate = false;

void setup()
{
  Serial.begin(9600);

  pinMode(8, OUTPUT);
  digitalWrite(8, HIGH);

  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);

  stepper.rotate();
}
int d1, d2 = 275;
void loop()
{
  if (Serial.available()){
    if(Serial.peek() != 10){
      d2 = Serial.parseInt();
      d1 = d2 / 1000;
      d2 = d2 - (d1*1000);
      //setStepper(d1, d2);
    } 
    else {
      while(Serial.read() != -1); 
    }
  }

  volatile int pos = analogRead(A3)>>1;
  volatile int diff = d2 - pos;
  // digitalWrite(13, HIGH);
  //delay(9);

  Serial.print(pos);
//  digitalWrite(13, LOW);


  Serial.print(", ");
//  delay(3);

  Serial.println(diff);
  //delay(3);

  if(abs(diff) > 5){
    digitalWrite(8, HIGH);
    stepper.rotate();
    if(signbit(diff))    
      stepper.setDirection(CW);
    else 
      stepper.setDirection(CCW);
  }  
  else{
    stepper.setDirection(STOP);
    digitalWrite(8, LOW);    
  }

  stepper.run();
}

