#include "Vibrator.h"

Vibrator::Vibrator(){
	this->vVibratorPin=4;
	this->vVibrationDuration = 20;
	this->vVibratorStatus=LOW;
	pinMode(this->vVibratorPin, OUTPUT);
}

Vibrator::~Vibrator(){

}

Vibrator::Vibrator(int pVibPin){
	this->vVibratorPin = pVibPin;
	this->vVibrationDuration = 20;
	this->vVibratorStatus = LOW;
	pinMode(this->vVibratorPin, OUTPUT);
}

Vibrator::Vibrator(int pVibPin, int pVibDuration){
	this->vVibratorPin = pVibPin;
	this->vVibrationDuration = pVibDuration;
	this->vVibratorStatus = LOW;
	pinMode(this->vVibratorPin, OUTPUT);
}

void Vibrator::vibrate(void){
	digitalWrite(this->vVibratorPin, HIGH);
	delay(this->vVibrationDuration);
	digitalWrite(this->vVibratorPin, LOW);
}

void Vibrator::vibrateOn(void){
	digitalWrite(this->vVibratorPin, HIGH);
	this->vVibratorStatus = HIGH;
}

void Vibrator::vibrateOff(void){
	digitalWrite(this->vVibratorPin, LOW);
	this->vVibratorStatus = LOW;
}

int Vibrator::getVibratorStatus(void){
	return this->vVibratorStatus;
}

void Vibrator::setVibPin(int pVibPin){
	this->vVibratorPin = pVibPin;
	pinMode(this->vVibratorPin, OUTPUT);
}

int Vibrator::getVibPin(void){
	return this->vVibratorPin;
}

void Vibrator::setVibrationDuration(int pVibDuration){
	this->vVibrationDuration = pVibDuration;
}

int Vibrator::getVibrationDuration(void){
	return this->vVibrationDuration;
}
