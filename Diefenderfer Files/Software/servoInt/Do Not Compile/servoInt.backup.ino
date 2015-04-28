#include "MotorInt.h"

// ================================================================
//  Set the Serial monitor to terminate on newline!
//
//  This functionality is optimized for use with a
//  GUI that sends strings to the serial port using
//  a println function
// ================================================================

/*
byte curPos[NUM_MOTORS] = {
 0};
 byte finalPos[NUM_MOTORS] = {
 0};
 boolean dir[NUM_MOTORS] = {
 false};
 */

MotorInt motors;

void setup(){
  Serial.begin(9600);
  /*
  pinMode(A0, INPUT);
   pinMode(A1, INPUT);
   pinMode(2, OUTPUT);
   pinMode(3, OUTPUT);
   pinMode(4, OUTPUT);
   pinMode(5, OUTPUT);
   */
  // O-scope Debug Pins
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);

  /*
  digitalWrite(2, LOW);
   digitalWrite(3, LOW);
   digitalWrite(4, LOW);
   digitalWrite(5, LOW);
   
   finalPos[0] = 128;
   finalPos[1] = 128;
   
   // don't touch this
   ADMUX |= 0x60;   // prep ADC MUX
   ADMUX &= 0xf0;   // clear MUX channel
   ADCSRA |= 0xCF;  // prep ADC settings and start ADC
   sei();  // enable global interrupts
   */
}

int d1,d2 = 0;

void loop(){
  if(Serial.available()){
    if(Serial.peek() != 10){
      d2 = Serial.parseInt();

      d1 = d2 / 1000;        // trust me, this will work
      d2 = d2 - (d1*1000);
      //finalPos[d1] = d2;
      motors.setMotor(d1, d2);
    } 
    else {
      while(Serial.read() != -1); 
    }
  }

  // WCET 50 us
  digitalWrite(13, HIGH); // ============================= O-scope
  motors.updateMotors(); 
  digitalWrite(13, LOW); // ============================= O-scope

  /*
  // WCET 10 ms ouch...
   Serial.print(curPos[0]);
   Serial.print(", ");
   Serial.println(curPos[1]);
   
   */
}

/*
inline void updateMotors(){
 
 boolean DltP = false;
 DltP = finalPos[0] < curPos[0];
 if (!DltP){
 digitalWrite(2, LOW);
 dir[0] = false;
 }
 else{
 digitalWrite(2, HIGH);
 dir[0] = true;
 }
 int temp = abs(finalPos[0] - curPos[0]);
 if (temp > 2)
 analogWrite(3, 255); // start motor
 if (dir[0] ^ DltP)   // check for motor overshoot
 analogWrite(3, 0); // halt
 else {
 if (temp <= 2)         // check within threshold
 analogWrite(3, 0);  // stop motor
 else if (temp < 45)
 {
 temp = (temp << 2) + 70;
 analogWrite(3, temp);
 }
 else 
 analogWrite(3, 255);
 }
 
 
 DltP = finalPos[1] < curPos[1];
 if (!DltP){
 digitalWrite(4, LOW);
 dir[1] = false;
 }
 else{
 digitalWrite(4, HIGH);
 dir[1] = true;
 }
 temp = abs(finalPos[1] - curPos[1]);
 if (temp > 2)
 analogWrite(5, 255); // start motor
 if (dir[1] ^ DltP)   // check for motor overshoot
 analogWrite(5, 0); // halt
 else {
 if (temp <= 2)         // check within threshold
 analogWrite(5, 0);  // stop motor
 else if (temp < 45)
 {
 temp = (temp << 2) + 70;
 analogWrite(5, temp);
 }
 else 
 analogWrite(5, 255);
 }
 
 }
 
 ISR(ADC_vect) {
 digitalWrite(12, HIGH); // ============================= O-scope
 byte channel = ADMUX & 0x0f;   // get current channel
 curPos[channel] = ADCH;
 ADMUX ^= 0x01;   // set MUX channel
 ADCSRA |= 0x40; // start ADC
 digitalWrite(12, LOW); // ============================= O-scope
 };
 */





