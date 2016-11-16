
#include <Arduino.h>
#ifndef SENSNUMREADINGS
#define SENSNUMREADINGS 10
#endif

class Sensor{

protected:
	int vSensorMinValue = 0;
	int vSensorMaxValue = 1000;
	int vSensorValue = 0;
	int vSensorPin = A5;
	int vReadings[SENSNUMREADINGS];
	int vReadIndex=0;
	int vTotal=0;
	int vAverage=0;
	int vPullDownResistor = 10000;	//default resistor value - 10K ohm

public:
	Sensor();
	Sensor(int pSensorPin);
	int sense(void);
	int getSensorMinValue(void);
	void setSensorMinValue(int pValue);
	int getSensorMaxValue(void);
	void setSensorMaxValue(int pValue);
	int getSensorPin(void);
	void setSensorPin(int pSensorPin);
	int getRawSensorValue(void);
	int getPullDownResistorVal(void);
	void setPullDownResistorVal(int pValue);
};
