#include "Arduino.h"
#include "steppermotor.h"
#include "assert.h"

//time to wait after each individual magnet assignment
#define MOTOR_COOLDOWN_TIME_MICROS 1500
#define STEPS_PER_DEGREE 12

StepperMotor::StepperMotor(byte o,byte y,byte p,byte b,byte debug):
	_state(0),
	_pin_orange(o),
	_pin_yellow(y),
	_pin_pink(p),
	_pin_blue(b),
	_debug(debug)
{setPinModes();}

StepperMotor::StepperMotor(byte o,byte y,byte p,byte b):
	_state(0),
	_pin_orange(o),
	_pin_yellow(y),
	_pin_pink(p),
	_pin_blue(b),
	_debug(false)
{setPinModes();}

//Auxiliary method which initializes the assigned pins
void StepperMotor::setPinModes(){
	pinMode(_pin_orange,OUTPUT);
	pinMode(_pin_yellow,OUTPUT);
	pinMode(_pin_pink,OUTPUT);
	pinMode(_pin_blue,OUTPUT);
}

void StepperMotor::singleStep(byte reverse,byte stepmode){
	if(stepmode==MODE_HALFSTEP){
		this->halfStep(reverse);
	}else if(stepmode==MODE_FULLSTEP){
		this->fullStep(reverse);
	}else{
		assert(false);
	}
	_state=(_state+1)%8;
	delayMicroseconds(MOTOR_COOLDOWN_TIME_MICROS);
	//delayMicroseconds(2000);
}

void StepperMotor::turn(byte reverse, int degrees, byte stepmode){
	byte _reverse = reverse;
	
	//flip direction if degrees are negative
	if(degrees<0){
		_reverse = !reverse;
	}
	
	//perform the required amount of steps
	for(unsigned int i = 0;i<degrees*STEPS_PER_DEGREE;i++){
		singleStep(_reverse,stepmode);
	}
}

void StepperMotor::setPins(byte o, byte y, byte p, byte b,byte reverse){
	digitalWrite(_pin_orange,reverse?b:o);
	digitalWrite(_pin_yellow,reverse?p:y);
	digitalWrite(_pin_pink,reverse?y:p);
	digitalWrite(_pin_blue,reverse?o:b);
}

void StepperMotor::fullStep(byte reverse){
  switch(_state){
     case 0:
     case 1:{
        setPins(HIGH,HIGH,LOW,LOW,reverse);
        break;
     }
     case 2:
     case 3:{
       setPins(LOW,HIGH,HIGH,LOW,reverse);
       break;
     }
     case 4:
     case 5:{
       setPins(LOW,LOW,HIGH,HIGH,reverse);
       break;
     }
     case 6:
     case 7:{
       setPins(HIGH,LOW,LOW,HIGH,reverse);
       break;       
     }
  }
}

void StepperMotor::halfStep(byte reverse){
	switch(this->_state){
		case 0:{
			this->setPins(HIGH,LOW,LOW,LOW,reverse);
			break;
		}
		case 1:{
			this->setPins(HIGH,HIGH,LOW,LOW,reverse);
			break;
		}
		case 2:{
			this->setPins(LOW,HIGH,LOW,LOW,reverse);
			break;
		}
		case 3:{
			this->setPins(LOW,HIGH,HIGH,LOW,reverse);
			break;
		}
		case 4:{
			this->setPins(LOW,LOW,HIGH,LOW,reverse);
			break;
		}
		case 5:{
			this->setPins(LOW,LOW,HIGH,HIGH,reverse);
			break;
		}
		case 6:{
			this->setPins(LOW,LOW,LOW,HIGH,reverse);
			break;
		}
		case 7:{
			this->setPins(HIGH,LOW,LOW,HIGH,reverse);
			break;       
		}
	}
}
