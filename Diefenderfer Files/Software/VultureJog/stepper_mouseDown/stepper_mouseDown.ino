#include <Stepper.h>

#define shoulderDirPin  2
#define shoulderPWMPin  3
#define neckDirPin  4
#define neckPWMPin  5

#define enPin        8
#define x1StepperPin 9
#define x2StepperPin 10
#define y1StepperPin 11
#define y2StepperPin 12
#define syncPin      13

Stepper xStepper = Stepper(100, x1StepperPin, x2StepperPin);
Stepper yStepper = Stepper(100, y1StepperPin, y2StepperPin);

void setup() {                

  Serial.begin(9600);

  xStepper.setSpeed(60);
  yStepper.setSpeed(60);
  pinMode(syncPin, OUTPUT);
  digitalWrite(syncPin, LOW);
  pinMode(enPin, OUTPUT);
  digitalWrite(enPin, LOW);

  pinMode(shoulderDirPin, OUTPUT);
  pinMode(shoulderPWMPin, OUTPUT);
  pinMode(neckDirPin, OUTPUT);
  pinMode(neckPWMPin, OUTPUT);
}
int data = 0;
int shoulderSpeed = 0;
int neckSpeed = 0;
void loop() {
  if (Serial.available()) {
    if (Serial.peek() != 10){ //make sure it is not a New Line char
      data = Serial.parseInt();
      switch(data){
      case 10:
        digitalWrite(syncPin, LOW);
        break;
      case 11:
        digitalWrite(syncPin, HIGH);
        break;
      case 12:
        digitalWrite(enPin, LOW);
        break;
      case 13:
        digitalWrite(enPin, HIGH);
        break;
      case 14:
        shoulderSpeed = parseNext();
        break;
      case 15:
        neckSpeed = parseNext();
        break;
      case 20:
        // nada
        break;
      case 21:
        xStepper.step(2);      
        break;
      case 22:
        xStepper.step(-2);
        break;
      case 23:
        yStepper.step(2);
        break;
      case 24:
        yStepper.step(-2);
        break;
      case 30:
        digitalWrite(shoulderDirPin, LOW);
        analogWrite(shoulderPWMPin, 0);
        digitalWrite(neckDirPin, LOW);
        analogWrite(neckPWMPin, 0);
        break;
      case 31:
        digitalWrite(shoulderDirPin, LOW);
        analogWrite(shoulderPWMPin, shoulderSpeed);
        break;
      case 32:
        digitalWrite(shoulderDirPin, HIGH);
        analogWrite(shoulderPWMPin, shoulderSpeed);
        break;
      case 33:
        digitalWrite(neckDirPin, LOW);
        analogWrite(neckPWMPin, neckSpeed);
        break;
      case 34:
        digitalWrite(neckDirPin, HIGH);
        analogWrite(neckPWMPin, neckSpeed);
        break;
      default:
        // do nothing
        break;
      }
    } 
    else {
      while(Serial.read() != -1 ); // flush incoming buffer
    }
  } 
  else {
    switch(data){
    case 10:
      digitalWrite(syncPin, LOW);
      break;
    case 11:
      digitalWrite(syncPin, HIGH);
      break;
    case 12:
      digitalWrite(enPin, LOW);
      break;
    case 13:
      digitalWrite(enPin, HIGH);
      break;
    case 20:
      // nada
      break;
    case 21:
      xStepper.step(2);      
      break;
    case 22:
      xStepper.step(-2);
      break;
    case 23:
      yStepper.step(2);
      break;
    case 24:
      yStepper.step(-2);
      break;
    case 30:
      digitalWrite(shoulderDirPin, LOW);
      analogWrite(shoulderPWMPin, 0);
      digitalWrite(neckDirPin, LOW);
      analogWrite(neckPWMPin, 0);
      break;
    case 31:
      digitalWrite(shoulderDirPin, LOW);
      analogWrite(shoulderPWMPin, shoulderSpeed);
      break;
    case 32:
      digitalWrite(shoulderDirPin, HIGH);
      analogWrite(shoulderPWMPin, shoulderSpeed);
      break;
    case 33:
      digitalWrite(neckDirPin, LOW);
      analogWrite(neckPWMPin, neckSpeed);
      break;
    case 34:
      digitalWrite(neckDirPin, HIGH);
      analogWrite(neckPWMPin, neckSpeed);
      break;
    default:
      // do nothing
      break;
    }
  }
}

int parseNext(){
  int pData =0;
  while (1) {
    if (Serial.available()) {
      if (Serial.peek() != 10){ //make sure it is not a New Line char
        pData = Serial.parseInt();
        while(Serial.read() != -1 ); // flush incoming buffer
        return pData;
      } 
      else {
        while(Serial.read() != -1 ); // flush incoming buffer
      }
    }
  } 
}









