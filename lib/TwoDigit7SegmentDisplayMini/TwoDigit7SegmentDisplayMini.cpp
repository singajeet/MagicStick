#include "TwoDigit7SegmentDisplayMini.h"

TwoDigit7SegmentDisplayMini::TwoDigit7SegmentDisplayMini(){

}

TwoDigit7SegmentDisplayMini::~TwoDigit7SegmentDisplayMini(){

}

#ifdef SEG7_VERSION1
  TwoDigit7SegmentDisplayMini::TwoDigit7SegmentDisplayMini(int8_t pDataPin, int8_t pClockPin, int8_t pLatchPin, int8_t pTransistorPin){
     //Set the clock, data, transistor and latch pin
    this->vDataPin = pDataPin;
    this->vClockPin = pClockPin;
    this->vLatchPin = pLatchPin;
    this->vTransistorPin = pTransistorPin;

    pinMode(this->vDataPin, OUTPUT);
    pinMode(this->vClockPin, OUTPUT);
    pinMode(this->vLatchPin, OUTPUT);
    pinMode(this->vTransistorPin, OUTPUT);

    //Initialize the display to show 0
    digitalWrite(this->vLatchPin, LOW);
    shiftOut(this->vDataPin, this->vClockPin, MSBFIRST, 0);
    digitalWrite(this->vLatchPin, HIGH);
  }
#else
  TwoDigit7SegmentDisplayMini::TwoDigit7SegmentDisplayMini(int8_t pDataPin, int8_t pClockPin, int8_t pLatchPin, int8_t pSevenSegPin1, int8_t pSevenSegPin2){
     //Set the clock, data, transistor and latch pin
    this->vDataPin = pDataPin;
    this->vClockPin = pClockPin;
    this->vLatchPin = pLatchPin;
    this->vSevenSegPin1 = pSevenSegPin1;
    this->vSevenSegPin2 = pSevenSegPin2;

    pinMode(this->vDataPin, OUTPUT);
    pinMode(this->vClockPin, OUTPUT);
    pinMode(this->vLatchPin, OUTPUT);
    pinMode(this->vSevenSegPin1, OUTPUT);
    pinMode(this->vSevenSegPin2, OUTPUT);

    //Initialize the display to show 0
    digitalWrite(this->vLatchPin, LOW);
    shiftOut(this->vDataPin, this->vClockPin, MSBFIRST, 0);
    digitalWrite(this->vLatchPin, HIGH);
  }
#endif

#ifdef SEG7_VERSION1
  void TwoDigit7SegmentDisplayMini::setup(int8_t pDataPin, int8_t pClockPin, int8_t pLatchPin, int8_t pTransistorPin){
    //Set the clock, data, transistor and latch pin
    this->vDataPin = pDataPin;
    this->vClockPin = pClockPin;
    this->vLatchPin = pLatchPin;
    this->vTransistorPin = pTransistorPin;

    pinMode(this->vDataPin, OUTPUT);
    pinMode(this->vClockPin, OUTPUT);
    pinMode(this->vLatchPin, OUTPUT);
    pinMode(this->vTransistorPin, OUTPUT);

    //Initialize the display to show 0
    digitalWrite(this->vLatchPin, LOW);
    shiftOut(this->vDataPin, this->vClockPin, MSBFIRST, 0);
    digitalWrite(this->vLatchPin, HIGH);
  }
#else
  void TwoDigit7SegmentDisplayMini::setup(int8_t pDataPin, int8_t pClockPin, int8_t pLatchPin, int8_t pSevenSegPin1, int8_t pSevenSegPin2){
    //Set the clock, data, transistor and latch pin
    this->vDataPin = pDataPin;
    this->vClockPin = pClockPin;
    this->vLatchPin = pLatchPin;
    this->vSevenSegPin1 = pSevenSegPin1;
    this->vSevenSegPin2 = pSevenSegPin2;

    pinMode(this->vDataPin, OUTPUT);
    pinMode(this->vClockPin, OUTPUT);
    pinMode(this->vLatchPin, OUTPUT);
    pinMode(this->vSevenSegPin1, OUTPUT);
    pinMode(this->vSevenSegPin2, OUTPUT);

    //Initialize the display to show 0
    digitalWrite(this->vLatchPin, LOW);
    shiftOut(this->vDataPin, this->vClockPin, MSBFIRST, 0);
    digitalWrite(this->vLatchPin, HIGH);
  }
#endif

void TwoDigit7SegmentDisplayMini::print(int8_t pDigit){
  this->twoDigitInt2Str(pDigit);
}

void TwoDigit7SegmentDisplayMini::print(char *pBuffer){

}

void TwoDigit7SegmentDisplayMini::setRefreshRate(int8_t pValue){
  this->vRefreshRate = pValue;
}

int8_t TwoDigit7SegmentDisplayMini::getRefreshRate(){
  return this->vRefreshRate;
}

void TwoDigit7SegmentDisplayMini::twoDigitInt2Str(int8_t pDigit){
  int8_t digitOne = 0;
  int8_t digitTwo = 0;

  if(pDigit == 0){
      digitOne = 0;
      digitTwo = 0;
    }
  else if(pDigit < 10){
      digitOne = 0;
      digitTwo = pDigit;
    }
  else {
    digitOne = pDigit / 10;
    digitTwo = pDigit % 10;
  }

  #ifdef SEG7_VERSION1
    digitalWrite(this->vTransistorPin, HIGH);
    this->sendDigitBits(digitOne);
    delay(vRefreshRate);

    digitalWrite(this->vTransistorPin, LOW);
    this->sendDigitBits(digitTwo);
    delay(vRefreshRate);
  #else
    digitalWrite(this->vSevenSegPin1, HIGH);
    this->sendDigitBits(digitOne);
    delay(vRefreshRate);
    digitalWrite(this->vSevenSegPin1, LOW);

    digitalWrite(this->vSevenSegPin2, HIGH);
    this->sendDigitBits(digitTwo);
    delay(vRefreshRate);
    digitalWrite(this->vSevenSegPin2, LOW);
  #endif
}

void TwoDigit7SegmentDisplayMini::sendDigitBits(int8_t pDigit){
  digitalWrite(this->vLatchPin, LOW);
  switch(pDigit){
      case 0:
        shiftOut(this->vDataPin, this->vClockPin, MSBFIRST, this->vDigit0);
        break;
      case 1:
        shiftOut(this->vDataPin, this->vClockPin, MSBFIRST, this->vDigit1);
        break;
      case 2:
        shiftOut(this->vDataPin, this->vClockPin, MSBFIRST, this->vDigit2);
        break;
      case 3:
        shiftOut(this->vDataPin, this->vClockPin, MSBFIRST, this->vDigit3);
        break;
      case 4:
        shiftOut(this->vDataPin, this->vClockPin, MSBFIRST, this->vDigit4);
        break;
      case 5:
        shiftOut(this->vDataPin, this->vClockPin, MSBFIRST, this->vDigit5);
        break;
      case 6:
        shiftOut(this->vDataPin, this->vClockPin, MSBFIRST, this->vDigit6);
        break;
      case 7:
        shiftOut(this->vDataPin, this->vClockPin, MSBFIRST, this->vDigit7);
        break;
      case 8:
        shiftOut(this->vDataPin, this->vClockPin, MSBFIRST, this->vDigit8);
        break;
      case 9:
        shiftOut(this->vDataPin, this->vClockPin, MSBFIRST, this->vDigit9);
        break;
    }
    digitalWrite(this->vLatchPin, HIGH);
}
