#include "arduino.h"

#define assert(e) if(!e){byte state = HIGH;while(true){digitalWrite(13,state);state = state==HIGH?LOW:HIGH;delay(100);}}