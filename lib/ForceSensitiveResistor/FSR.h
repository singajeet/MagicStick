#include <Sensor.h>
#include <Arduino.h>

class FSR: public Sensor {
	private:
		int vFsrVoltage;
		unsigned long vFsrResistance;
		unsigned long vFsrConductance;
		long vFsrForce;

	public:
		FSR();
		FSR(int pSensorPin);
		int getFSRVoltage(void);
		unsigned long getFSRResistance(void);
		unsigned long getFSRConductance(void);
		long getFSRForce(void);
};
