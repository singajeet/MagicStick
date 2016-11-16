#include <Arduino.h>

#ifndef LED
#define LED

class Led{

private:
  int8_t vLedPin;
  int8_t vLedStatus;

public:
  Led();
  Led(int8_t pLedPin);
  void setLedPin(int8_t pLedPin);
  int8_t getLedPin(void);
  int8_t getLedStatus(void);
  void on(void);
  void off(void);
  void blink(void);
};

#endif
