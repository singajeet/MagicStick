#include <Arduino.h>
#include <TwoDigit7SegmentDisplayMini.h>
#include <Led.h>
#include <FSR.h>
#include <Vibrator595.h>
#include <PushButton.h>
#include <Bounce2.h>
#include <Button.h>
#include <ButtonEventCallback.h>
#include <Timer.h>
#include <CmdMessenger.h>


const byte latchPin = 10;
const byte clockPin = 11;
const byte dataPin = 12;

#ifdef SEG7_VERSION1
  const byte transistorPin = 9;
  const byte thresholdPin = 6;
#else
  const byte sevenSegPin1 = 9;
  const byte sevenSegPin2 = 6;
  const byte thresholdPin = A4;
#endif

const byte buttonPin = 8;
const byte sensorPin = A5;
const byte ledPin = 13;

const byte vibLatchPin = 4;
const byte vibDataPin = 5;
const byte vibClockPin = 7;

int sensorValue = 0;
byte isSetupMode = 0;
byte vibratorStatus = 0;
int sensorReadEventHandle;
int displayWriteEventHandle;
int vibrateEventHandle;
int sensorThreshHoldValue;

CmdMessenger cmdMessenger = CmdMessenger(Serial);

enum{
    kAcknowledge,
    kError,
    kGetSensorValue
};

enum VibrateStyle{
  VIB_ONE_AT_TIME,
  VIB_ALL_AUTO,
  VIB_ALL_MAN
};

VibrateStyle currentVibStyle = VIB_ALL_AUTO;
#ifdef SEG7_VERSION1
  TwoDigit7SegmentDisplayMini display(dataPin, clockPin, latchPin, transistorPin);
#else
  TwoDigit7SegmentDisplayMini display(dataPin, clockPin, latchPin, sevenSegPin1, sevenSegPin2);
#endif

PushButton button(buttonPin);
FSR fsr(sensorPin);
Led led(ledPin);
Vibrator595 vib(vibLatchPin, vibDataPin, vibClockPin);
Timer timer;

void OnUnknownCommand(){
  cmdMessenger.sendCmd(kError, "Unknown Command");
}

void OnGetSensorValueCommand(){
  cmdMessenger.sendCmd(kAcknowledge, sensorValue);
}

void attachCommandCallbacks(){
  cmdMessenger.attach(OnUnknownCommand);
  cmdMessenger.attach(kGetSensorValue, OnGetSensorValueCommand);
}

void onButtonPressed(Button& bttn){
  if(isSetupMode == 0){
    isSetupMode = 1;
    led.on();
  }
  else{
    isSetupMode = 0;
    led.off();
  }
}

void sensorReadEventCallback(){
  if(isSetupMode == 0)
    sensorValue = fsr.sense();
  else
    sensorThreshHoldValue = analogRead(thresholdPin);
}

void displayWriteEventCallback(){
  if(isSetupMode == 0)
    display.print(sensorValue);
  else
    display.print(sensorThreshHoldValue);
}

void vibrateEventCallback()
{
  if(sensorValue > sensorThreshHoldValue){
    if(vibratorStatus == LOW)
    {
      //put vibrator on
      vib.vibrateOn();
      vibratorStatus = HIGH;
    }
  } else
  {
    if(vibratorStatus == HIGH){
      //put vibrator off
      vib.vibrateOff();
      vibratorStatus = LOW;
    }
  }
}

void setup()
{
  //Register the callback for timers
  sensorReadEventHandle = timer.every(500, sensorReadEventCallback);
  displayWriteEventHandle = timer.every(250, displayWriteEventCallback);
  vibrateEventHandle = timer.every(600, vibrateEventCallback);
  //Register the callback for the button
  button.onPress(onButtonPressed);

  //Set pinmode for threshold pot
  pinMode(thresholdPin, INPUT);

  //Start serial comm and attach the callbacks
  Serial.begin(115200);
  attachCommandCallbacks();
  cmdMessenger.sendCmd(kAcknowledge, "MagicStick started!");
}

void loop()
{
  button.update();
  timer.update();
  cmdMessenger.feedinSerialData();
}
