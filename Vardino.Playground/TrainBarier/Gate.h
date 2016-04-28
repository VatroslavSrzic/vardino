// Gate.h

#ifndef _GATE_h
#define _GATE_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

#include "ErrorBase.h"
#include <Servo.h>

class GateClass : public ErrorBaseClass
{
public:
	GateClass(int servoPin, int servoMinPulseWidth = 572, int servoMaxPulseWidth = 2278);

	void Open();
	void Close();

	bool IsOpen();
	bool IsClose();

protected:
	int servoMinPulseWidth = -1;
	int servoMaxPulseWidth = -1;

	Servo servo;
	int servoControlPin = -1;

	void Attach();
	void Detach();

private:
};

#endif
