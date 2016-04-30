// Gate.h

#ifndef _GATE_h
#define _GATE_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

#include <Servo.h>
#include "ErrorBase.h"

class GateClass : public ErrorBaseClass
{
public:
	GateClass(int servoPin, int servoMinPulseWidth = 572, int servoMaxPulseWidth = 2278, int closeDeg = 83, int openDeg = 170);

	void Open();
	void Close();

	void Init();

	bool IsOpen();
	bool IsClose();

	bool IsInitialized();

protected:
	int servoMinPulseWidth = -1;
	int servoMaxPulseWidth = -1;

	int closeDeg = -1;
	int openDeg = -1;

	Servo servo;
	int servoControlPin = -1;

	void Attach();
	void Detach();

private:
	bool isInitialized = false;
};

#endif
