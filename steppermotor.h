#ifndef StepperMotor_h
#define StepperMotor_h

/**
* 28BYJ-48 5V stepper motor driver for use without a driver board
* Author: SwiftPengu
* 
* Connect the red wire to the 5V pin
*/
#include "Arduino.h"

#define MODE_FULLSTEP 0
#define MODE_HALFSTEP 1

#define CW true
#define CCW false

class StepperMotor{
public:
	StepperMotor(byte,byte,byte,byte);
	StepperMotor(byte,byte,byte,byte,byte);
	void singleStep(byte,byte);
	void turn(byte,int,byte);
	void fullStep(byte);
	void halfStep(byte);
private:	
	byte _pin_orange;
	byte _pin_yellow;
	byte _pin_pink;
	byte _pin_blue;

	byte _state;
	byte _debug;

	void setPinModes(void);
	void setPins(byte,byte,byte,byte,byte);
};
#endif
