#include "servoISR.h"

byte pos[NUM_MOTORS] = {0,0};
boolean dir[NUM_MOTORS] = {false, false};
byte pwmPins[NUM_MOTORS] = {0,0};
byte dirPins[NUM_MOTORS] = {0,0};
byte potPins[NUM_MOTORS] = {0,0};

servoISR::servoISR(byte dirPin, byte pwmPin, byte potPin, byte motorNum)
{ 
  pinMode(dirPin, OUTPUT);
  pinMode(pwmPin, OUTPUT);
  pinMode(potPin, OUTPUT);
  
  pwmPins[motorNum] = pwmPin;
  dirPins[motorNum] = dirPin;
  potPins[motorNum] = potPin;
  
  // don't touch this
  ADMUX |= 0x60;   // prep ADC MUX
  ADMUX &= 0xf0;   // clear MUX channel
  ADCSRA |= 0x8F;  // prep ADC settings
  sei();  // enable global interrupts
  // ADCSRA |= 0x40; // start ADC
}

void updateMotor(int motorNum){
  
}

ISR(ADC_vect) {
  byte channel = ADMUX & 0x0f;   // get current channel
  pos[channel] = ADCH; // this will need to change later
  ADMUX ^= 0x01;   // set MUX channel
  ADCSRA |= 0x40; // start ADC
};
