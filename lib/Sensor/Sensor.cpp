#include "Sensor.h"


  Sensor::Sensor(){
      for(int counter=0; counter<SENSNUMREADINGS; counter++){
        this->vReadings[counter] = 0;
      }

      pinMode(this->vSensorPin, INPUT);
    }

  Sensor::Sensor(int pSensorPin){
      this->vSensorPin = pSensorPin;
      for(int counter=0; counter<SENSNUMREADINGS; counter++){
        this->vReadings[counter] = 0;
      }

      pinMode(this->vSensorPin, INPUT);
    }

  int Sensor::getSensorMinValue(void){
    return this->vSensorMinValue;
  }

  void Sensor::setSensorMinValue(int pValue){
    this->vSensorMinValue = pValue;
  }

  int Sensor::getSensorMaxValue(void){
    return this->vSensorMaxValue;
  }

  void Sensor::setSensorMaxValue(int pValue){
    this->vSensorMaxValue = pValue;
  }

  int Sensor::getSensorPin(void){
    return this->vSensorPin;
  }

  void Sensor::setSensorPin(int pSensorPin){
    this->vSensorPin = pSensorPin;
    pinMode(this->vSensorPin, INPUT);
  }

  int Sensor::getRawSensorValue(void){
    return analogRead(this->vSensorPin);
  }

  int Sensor::getPullDownResistorVal(void){
    return this->vPullDownResistor;
  }

  void Sensor::setPullDownResistorVal(int pValue){
    this->vPullDownResistor = pValue;
  }

  void Sensor::normalize(){
    int max = analogRead(this->vSensorPin);
    for(int i=0; i < 10; i++){
      int sampleVal = analogRead(this->vSensorPin);
      if(sampleVal > max ){
        max = sampleVal;
      }
    }
    this->normalizeByVal = max;
  }

  int Sensor::sense(void)
  {
      this->vTotal = this->vTotal - this->vReadings[this->vReadIndex];
      this->vSensorValue = analogRead(this->vSensorPin);
      this->vSensorValue = constrain(this->vSensorValue, this->vSensorMinValue, this->vSensorMaxValue);

      this->vReadings[this->vReadIndex] = this->vSensorValue;
      this->vTotal = this->vTotal + this->vReadings[this->vReadIndex];
      this->vReadIndex += 1;

      if(this->vReadIndex >= SENSNUMREADINGS){
          this->vReadIndex = 0;
        }

       this->vAverage = this->vTotal / SENSNUMREADINGS;

       return this->vAverage - this->normalizeByVal;
  }
