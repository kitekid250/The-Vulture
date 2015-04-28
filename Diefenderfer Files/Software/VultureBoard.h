// to use this file in an Arduino sketch include the following line at the top:
// #include "VultureBoard.h"
// and place the file in the same folder as the .ino sketch file

#ifndef VULTURE_BOARD_H
#define VULTURE_BOARD_H

// stepper pins
#define SYNC 6 	// Matt, Drive this LOW. It synchronizes the steppers
				// and you don't want that.
#define EN 7 	// Drive this high when you want to move the motors

				// This board uses a 2-pin stepping scheme due to the
				// limitation of available pins
#define CNB0 9	// This and CNB1 drive the B stepper.
#define CNB1 A0	// Use it: Stepper stepA(400, CNB0, CNB1);

#define CNA0 8	// Same as above.
#define CNA1 10

// DC motor pins
#define DIRB 2	// Leave these alone. They are for DC motors
#define PWMB 3
#define DIRA 4
#define PWMA 5

// AUX Pins
#define RX 0	// Serial port pins, leave these alone
#define TX 1	// Simulink will need these

// 11-13 & A1-A5 are AUXILLARY and not labelled
#endif