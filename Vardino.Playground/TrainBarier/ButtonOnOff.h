// ButtonOnOff.h

#ifndef _BUTTONONOFF_h
#define _BUTTONONOFF_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

#include "ErrorBase.h"

class ButtonOnOffClass : public ErrorBaseClass
{
public:
	ButtonOnOffClass(int buttonPin);

	bool IsOn();
	bool IsOff();

protected:
	int digitalPin = -1;

private:
	bool GetOnOffState();
};

#endif
