#include "Arduino.h"
#include "steppermotor.h"
#include "assert.h"

#define PIN_ORANGE 12
#define PIN_YELLOW 11
#define PIN_PINK 10
#define PIN_BLUE 9

#define PIN_LED 13

StepperMotor* motor = NULL;
byte dir = CW;

void setup(){	
	pinMode(PIN_LED,OUTPUT);
	//pinMode(A0,INPUT);
	
	motor = new StepperMotor(PIN_ORANGE,PIN_YELLOW,PIN_PINK,PIN_BLUE);
}

void loop(){
	motor->turn(dir,90,MODE_HALFSTEP);
	//dir=!dir;
	delay(1000);
}
