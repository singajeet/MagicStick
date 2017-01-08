#include "Vibrator595.h"

Vibrator595::Vibrator595(){

}

Vibrator595::~Vibrator595(){

}

Vibrator595::Vibrator595(int pLatchPin, int pDataPin, int pClockPin){
  this->vLatchPin = pLatchPin;
  this->vDataPin = pDataPin;
  this->vClockPin = pClockPin;
}

void Vibrator595::vibrateOn(){

}

void Vibrator595::vibrateOff(){
  
}
