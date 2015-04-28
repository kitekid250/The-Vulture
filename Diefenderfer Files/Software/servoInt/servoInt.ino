#include <CustomStepper.h>
#include "MotorInt.h"

// ================================================================
//  Set the Serial monitor to terminate on newline!
//
//  This functionality is optimized for use with a
//  GUI that sends strings to the serial port using
//  a println function
// ================================================================

MotorInt motors;

void setup(){
  Serial.begin(9600);
}

int d1,d2 = 0;

void loop(){
  if(Serial.available()){
    if(Serial.peek() != 10){
      d2 = Serial.parseInt();
      d1 = d2 / 1000;
      d2 = d2 - (d1*1000);
      motors.setMotor(d1, d2);
    } 
    else {
      while(Serial.read() != -1); 
    }
  }
// Serial.println("loop");
  // WCET 50 us
  motors.updateMotors(); 

  
   // WCET 10 ms

   
 
}




