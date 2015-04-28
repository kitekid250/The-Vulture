#define STEPS_PER_REVOLUTION 100
#define NUM_MOTORS 2
#define STEPPER_EN 5
#define HALT_THRESHOLD 5

#include <CustomStepper.h>

CustomStepper stepper(6,7, (byte[]){
  4, B10, B11, B01, B00}
, STEPS_PER_REVOLUTION, 60, CW);
byte curPos[NUM_MOTORS];
byte finalPos[NUM_MOTORS];
boolean dir[NUM_MOTORS];
boolean moveDone[NUM_MOTORS];

int d1,d2 = 0;
boolean DltP = false;

void setup() {
  pinMode(13, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(A0, INPUT);
  
  pinMode(STEPPER_EN, OUTPUT);
  digitalWrite(STEPPER_EN, HIGH);
  stepper.setRPM(60);
  stepper.setSPR(100);
  Serial.begin(9600);

  finalPos[0] = 164;
/*
  // don't touch this
  ADMUX |= 0x60;   // prep ADC MUX
  ADMUX &= 0xf0;   // clear MUX channel
  ADCSRA |= 0xCF;  // prep ADC settings and start ADC
  sei();  // enable global interrupts  
 */ 
}

void loop() {
  if (Serial.available()){
    if(Serial.peek() != 10){
      d2 = Serial.parseInt();
      d1 = d2 / 1000;
      d2 = d2 - (d1*1000);
      setStepper(d1, d2);
    } 
    else {
      while(Serial.read() != -1); 
    }
  }
  //Serial.println("updating steppers");
  
  updateSteppers();
  //Serial.println("running steppers");
  Serial.println("Enter Run");
  stepper.run();
  Serial.println("Exit Run");
}

void setStepper(int motor, int pos){
    Serial.println("In Set");
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
    // stepper.rotate();

    DltP = finalPos[0] < curPos[0];

    if (!DltP){
      stepper.setDirection(CW);
      stepper.rotate();
      dir[0] = false;
      //    delay(1);
      //Serial.println("CW");
    }
    else{
      stepper.setDirection(CCW);
      stepper.rotate();
      dir[0] = true;
      //delay(1);
      //Serial.println("CCW");
    }
  }
}

void updateSteppers(){
  Serial.println("In Update");
  //  boolean DltP = false;
  curPos[0] = analogRead(A0);
  int absDist = abs(finalPos[0] - curPos[0]);

  if (moveDone[0] || (dir[0] ^ DltP)){   // check for motor overshoot
    // stepper.setDirection(STOP);
    digitalWrite(STEPPER_EN, LOW);  
    moveDone[0] = true;
    // Serial.println("Halt stepper");
  }
  else if (absDist <= HALT_THRESHOLD){         // check within threshold
    // stepper.setDirection(STOP);
    digitalWrite(STEPPER_EN, LOW);  
    moveDone[0] = true;
    // Serial.println("Halt stepper");
  } 
  else {
    digitalWrite(STEPPER_EN, HIGH); 
  }
}

/*
ISR(ADC_vect) {
  digitalWrite(13, HIGH);
  byte channel = ADMUX & 0x0f;   // get current channel
  curPos[channel] = ADCH;
  ADMUX = ADMUX ^ 1;   // set MUX channel
  ADCSRA |= 0x40; // start ADC
  digitalWrite(13, LOW);
};
*/
