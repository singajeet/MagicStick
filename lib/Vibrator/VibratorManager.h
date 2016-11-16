#include <Arduino.h>
#include <Vibrator.h>

#ifndef VIBRATORMANAGER
#define VIBRATORMANAGER

class VibratorArray{

private:
	int vNumberOfVibrators=5;
	int vVibratorIndex;
	Vibrator *pointerToVibrators;
	int vDelayBetweenVibrate=15;

public:
	VibratorArray();
	~VibratorArray();
	VibratorArray(int pValue);
	void create(int pValue);
	void del(void);
	void setDelayBetweenVibrate(int pValue);
	int getDelayBetweenVibrate(void);
	void vibrateOneAtTime(void);
	void vibrateOneAtTime(int pDelayBetweenVibrate);
	void vibrateAll(void);
	void vibrateOnAll(void);
	void vibrateOffAll(void);
	Vibrator* getPointerToVibrators(void);
};

#endif
