// ButtonOnOff.h

#ifndef _BUTTONONOFF_h
#define _BUTTONONOFF_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

class ButtonOnOffClass
{
public:
	ButtonOnOffClass(int buttonPort);

	bool InError();
	String GetErrorText();

	bool IsOn();
	bool IsOff();

protected:
	int digitalPin = -1;

	void ClearErrr();

	void SetError(String errorText);

private:
	bool inError = false;
	String errorText = "";

	bool GetOnOffState();
};

#endif
