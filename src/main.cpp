#include <Arduino.h>
#include <TwoDigit7SegmentDisplayMini.h>
#include <Led.h>
#include <FSR.h>
#include <VibratorManager.h>
#include <PushButton.h>
#include <Bounce2.h>
#include <Button.h>
#include <ButtonEventCallback.h>


const byte latchPin = 10;
const byte clockPin = 11;
const byte dataPin = 12;
const byte transistorPin = 9;
const byte buttonPin = 8;
const byte sensorPin = A5;
const byte ledPin = 13;
const byte firstVibPin = 4;
const byte secondVibPin = 5;
const byte thirdVibPin = 6;
const byte fourthVibPin = 7;
byte sensorValue = 0;

enum VibratorSequence{
  FIRST_VIB = 0,
  SECOND_VIB = 1,
  THIRD_VIB = 2,
  FOURTH_VIB = 3
};

enum VibrateStyle{
  VIB_ONE_AT_TIME,
  VIB_ALL_AUTO,
  VIB_ALL_MAN
};

VibrateStyle currentVibStyle = VIB_ALL_AUTO;

TwoDigit7SegmentDisplayMini display(dataPin, clockPin, latchPin, transistorPin);
PushButton button(buttonPin);
FSR fsr(sensorPin);
Led led(ledPin);
VibratorArray vibArray(4);
Vibrator *pointerToVibrators;

void onButtonPressed(Button& bttn){
  if(currentVibStyle == VIB_ALL_AUTO){
    currentVibStyle = VIB_ALL_MAN;
    led.blink();
  }
  else if(currentVibStyle == VIB_ALL_MAN){
    currentVibStyle = VIB_ONE_AT_TIME;
    led.blink();
  }
  else{
    currentVibStyle = VIB_ALL_AUTO;
    led.blink();
  }
}

void setup()
{
  //Setup the pins for each vibrator used
  pointerToVibrators = vibArray.getPointerToVibrators();
  pointerToVibrators[FIRST_VIB].setVibPin(firstVibPin);
  pointerToVibrators[SECOND_VIB].setVibPin(secondVibPin);
  pointerToVibrators[THIRD_VIB].setVibPin(thirdVibPin);
  pointerToVibrators[FOURTH_VIB].setVibPin(fourthVibPin);

  //Register the callback for the button
  button.onPress(onButtonPressed);
  Serial.begin(19200);
}

void loop()
{
  button.update();
  sensorValue = fsr.sense();
  display.print(sensorValue);

  Serial.println(sensorValue);

  // if(sensorValue > 5){
  //   if(currentVibStyle == VIB_ALL_AUTO)
  //     vibArray.vibrateAll();
  //   else if(currentVibStyle == VIB_ALL_MAN)
  //   {
  //     vibArray.vibrateOnAll();
  //     delay(40);
  //     vibArray.vibrateOffAll();
  //   }
  //   else if(currentVibStyle == VIB_ONE_AT_TIME)
  //     vibArray.vibrateOneAtTime();
  // }
}
