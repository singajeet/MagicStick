#include "VibratorManager.h"

VibratorArray::VibratorArray(){
	this->vVibratorIndex=0;
	this->pointerToVibrators = new Vibrator[4];
	this->vNumberOfVibrators = 4;
}

VibratorArray::VibratorArray(int pValue){
	this->vVibratorIndex=0;
	this->pointerToVibrators = new Vibrator[pValue];
	this->vNumberOfVibrators = pValue;
}

VibratorArray::~VibratorArray(){
	
}

void VibratorArray::create(int pValue){
	this->vVibratorIndex=0;
	this->pointerToVibrators = new Vibrator[pValue];
	this->vNumberOfVibrators = pValue;
}

void VibratorArray::del(void){
	delete this->pointerToVibrators;
}

void VibratorArray::setDelayBetweenVibrate(int pValue){
	this->vDelayBetweenVibrate = pValue;
}

int VibratorArray::getDelayBetweenVibrate(void){
		return this->vDelayBetweenVibrate;
}

void VibratorArray::vibrateOneAtTime(void){
		for(int count=0; count<this->vNumberOfVibrators; count++){
			this->pointerToVibrators[count].vibrate();
			delay(this->vDelayBetweenVibrate);
		}
}

void VibratorArray::vibrateOneAtTime(int pDelayBetweenVibrate){
	for(int count=0; count<this->vNumberOfVibrators; count++){
		this->pointerToVibrators[count].vibrate();
		delay(pDelayBetweenVibrate);
	}
}

void VibratorArray::vibrateAll(void){
	for(int count=0; count<this->vNumberOfVibrators; count++){
		this->pointerToVibrators[count].vibrate();
	}
}

void VibratorArray::vibrateOnAll(void){
	for(int count=0; count<this->vNumberOfVibrators; count++){
		this->pointerToVibrators[count].vibrateOn();
	}
}

void VibratorArray::vibrateOffAll(void){
	for(int count=0; count<this->vNumberOfVibrators; count++){
		this->pointerToVibrators[count].vibrateOff();
	}
}

Vibrator* VibratorArray::getPointerToVibrators(void){
	return this->pointerToVibrators;
}
