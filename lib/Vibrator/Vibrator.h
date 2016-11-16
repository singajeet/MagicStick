#include <Arduino.h>
#ifndef VIBRATOR
#define VIBRATOR

class Vibrator
{
private:
	int vVibratorPin;
	int vVibratorStatus;
	int vVibrationDuration;

public:
	Vibrator();
	Vibrator(int pVibPin);
	Vibrator(int pVibPin, int pVibDuration);
	~Vibrator();
	void vibrate(void);
	void vibrateOn(void);
	void vibrateOff(void);
	int getVibratorStatus(void);
	void setVibPin(int pVibPin);
	int getVibPin(void);
	int getVibrationDuration(void);
	void setVibrationDuration(int pVibDuration);
};

#endif