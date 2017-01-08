#include "Vibrator595.h"

Vibrator595::Vibrator595(){

}

Vibrator595::~Vibrator595(){

}

Vibrator595::Vibrator595(int pLatchPin, int pDataPin, int pClockPin){
  this->vLatchPin = pLatchPin;
  this->vDataPin = pDataPin;
  this->vClockPin = pClockPin;

  pinMode(this->vLatchPin, OUTPUT);
  pinMode(this->vDataPin, OUTPUT);
  pinMode(this->vClockPin, OUTPUT);

  digitalWrite(this->vLatchPin, LOW);
  shiftOut(this->vDataPin, this->vClockPin, MSBFIRST, 0);
  digitalWrite(this->vLatchPin, HIGH);
}

void Vibrator595::vibrateOn(){
  digitalWrite(this->vLatchPin, LOW);
  shiftOut(this->vDataPin, this->vClockPin, MSBFIRST, ((1 << 5) - 1));
  digitalWrite(this->vLatchPin, HIGH);
}

void Vibrator595::vibrateOff(){
  digitalWrite(this->vLatchPin, LOW);
  shiftOut(this->vDataPin, this->vClockPin, MSBFIRST, 0);
  digitalWrite(this->vLatchPin, HIGH);
}
