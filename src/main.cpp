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

//Serial comm speed
const int SERIAL_SPEED = 9600;

//Below pins to be used by 7 Segment
const byte latchPin = 10;
const byte clockPin = 11;
const byte dataPin = 12;

//VER1: 2 digits in Ver1 display are controlled by 2 transistors which further are controlled by uC using pin 9
//making pin9 high switch on one transistor and switch off the otherone and viceversa.
//Threshold pot is on pin 6 in this version
//VER2: 2 digits in Ver2 are controlled by uC directly using pin 9 and 6
//Threshold pot is connected to A4 in this version
#ifdef SEG7_VERSION1
  const byte transistorPin = 9;
  const byte thresholdPin = 6;
#else
  const byte sevenSegPin1 = 6;
  const byte sevenSegPin2 = 9;
  const byte thresholdPin = A4;
#endif

//button, FSR sensor and LED pins
const byte buttonPin = 8;
const byte sensorPin = A5;
const byte ledPin = 13;

//Vibrators are attached on below pins using 74HC595
const byte vibLatchPin = 7;
const byte vibDataPin = 5;
const byte vibClockPin = 4;

//Global variable to hold sensor value
int sensorValue = 0;

//Setup mode will allow to read threshold value from pot and display same on 7 seg
byte isSetupMode = 0;

//If high will keep vib's on until it goes low
byte vibratorStatus = 0;

//handlers to various events used in this program
int sensorReadEventHandle;
int displayWriteEventHandle;
int vibrateEventHandle;
int serialCommEventHandle;

//Pot threshold value
int sensorThreshHoldValue = 1000;

//Build 7 seg object based on the version selected, please see above comments
//for more information
#ifdef SEG7_VERSION1
  TwoDigit7SegmentDisplayMini display(dataPin, clockPin, latchPin, transistorPin);
#else
  TwoDigit7SegmentDisplayMini display(dataPin, clockPin, latchPin, sevenSegPin1, sevenSegPin2);
#endif

//Class object for various components used in this program
PushButton button(buttonPin);
FSR fsr(sensorPin);
Led led(ledPin);
Vibrator595 vib(vibLatchPin, vibDataPin, vibClockPin);
Timer timer;

//Button press event handler/callback
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

//Timer event scheduled to run every 10 sec
//Read either FSR or Pot depending upon setup mode selected
void sensorReadEventCallback(){
  if(isSetupMode == 0)
    sensorValue = fsr.sense();
  else
    sensorThreshHoldValue = analogRead(thresholdPin);
}

//Timer event scheduled to run every 5 sec
//Display value of either FSR or Pot depending upon setup mode selected
void displayWriteEventCallback(){
  if(isSetupMode == 0)
    display.print(sensorValue);
  else
    display.print(sensorThreshHoldValue);
}

//Timer event scheduled to run every 12 sec
//Switch on the vib's if FSR value is greater than threshold and keep it
//on unless the FSR value drops below the threshold
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

//Callback to send the sensor val back to PC
//Frame Structure: FS|FSR:<fsr reading>|POT:<pot reading>|FE
void serialCommEventCallback(){
  if(Serial.availableForWrite()){
    Serial.print("FS|");
    Serial.print("FSR:");
    Serial.print(sensorValue);
    Serial.print("|POT:");
    Serial.print(sensorThreshHoldValue);
    Serial.println("|FE");
    //Serial.flush();
  }
}

//Setup module
void setup()
{

  //Register the callback for timers
  sensorReadEventHandle = timer.every(10, sensorReadEventCallback);
  displayWriteEventHandle = timer.every(5, displayWriteEventCallback);
  vibrateEventHandle = timer.every(12, vibrateEventCallback);
  serialCommEventHandle = timer.every(60, serialCommEventCallback);

  //Register the callback for the button
  button.onPress(onButtonPressed);

  //Set pinmode for threshold pot
  pinMode(thresholdPin, INPUT);

  //Start serial comm
  Serial.begin(SERIAL_SPEED);

  while(!Serial){
    ; //Wait for serial port to connect
  }
}

void loop()
{
  button.update();
  timer.update();
}
