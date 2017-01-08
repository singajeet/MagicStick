#include <Arduino.h>
#ifndef VIBRATOR595
#define VIBRATOR595

class Vibrator595{
private:
  int vLatchPin;
  int vDataPin;
  int vClockPin;

public:
  Vibrator595();
  Vibrator595(int pLatchPin, int pDataPin, int pClockPin);
  ~Vibrator595();
  
  void vibrateOn(void);
  void vibrateOff(void);
};
#endif
