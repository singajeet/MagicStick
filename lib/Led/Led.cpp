#include "Led.h"

Led::Led(){
  this->vLedPin = 13;
  pinMode(this->vLedPin, OUTPUT);
  this->vLedStatus = LOW;
}

Led::Led(int8_t pLedPin){
  this->vLedPin = pLedPin;
  pinMode(this->vLedPin, OUTPUT);
  this->vLedStatus = LOW;
}

void Led::setLedPin(int8_t pLedPin){
  this -> vLedPin = pLedPin;
  pinMode(this->vLedPin, OUTPUT);
  this->vLedStatus = LOW;
}

int8_t Led::getLedPin(){
  return this->vLedPin;
}

int8_t Led::getLedStatus(){
  return this->vLedStatus;
}

void Led::on(){
  digitalWrite(this->vLedPin, HIGH);
  this->vLedStatus = HIGH;
}

void Led::off(){
  digitalWrite(this->vLedPin, LOW);
  this->vLedStatus = LOW;
}

void Led::blink(){
  digitalWrite(this->vLedPin, HIGH);
  delay(20);
  digitalWrite(this->vLedPin, LOW);
  delay(20);
}
