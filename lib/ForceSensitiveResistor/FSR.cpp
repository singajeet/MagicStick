#include "FSR.h"

FSR::FSR():Sensor(){

}

FSR::FSR(int pSensorPin):Sensor(pSensorPin){

}

int FSR::getFSRVoltage(void){
	// analog voltage reading ranges from about 0 to 1023 which maps to 0V to 5V (= 5000mV)
	this->vFsrVoltage = map(this->sense(), 0, 1023, 0, 5000);
	return this->vFsrVoltage;
}

unsigned long FSR::getFSRResistance(void){
	//get the voltage reading which will be stored in the member attribute
	int voltage = this->getFSRVoltage();
	if(voltage == 0){
		return 0;
	} else{
		this->vFsrResistance = 5000 - voltage;
		this->vFsrResistance *= this->vPullDownResistor;
		this->vFsrResistance /= voltage;
		return this->vFsrResistance;
	}
}

unsigned long FSR::getFSRConductance(void){
	this->vFsrConductance = 1000000;
	this->vFsrConductance /= this->getFSRResistance();
	return this->vFsrConductance;
}

long FSR::getFSRForce(void){
	int conductance = this->getFSRConductance();
	if(conductance <= 1000){
		this->vFsrForce = conductance / 80;
		return this->vFsrForce;
	} else {
		this->vFsrForce = conductance - 1000;
		this->vFsrForce /= 30;
		return this->vFsrForce;
	}
}
