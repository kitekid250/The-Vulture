
#define shoulderDirPin  2
#define shoulderPWMPin  3
#define neckDirPin  4
#define neckPWMPin  5


void setup() {                

  Serial.begin(9600);
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
      case 14:
        shoulderSpeed = parseNext();
        break;
      case 15:
        neckSpeed = parseNext();
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
  int pData;
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

