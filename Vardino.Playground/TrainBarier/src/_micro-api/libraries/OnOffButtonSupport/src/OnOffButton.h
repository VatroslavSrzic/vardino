// OnOffButton.h

#ifndef _ONOFFBUTTON_h
#define _ONOFFBUTTON_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

/*
		| Dig3 -------signal--------S |
Arduino	| 5V   ---------------------  |  Momentary Button
		| GND  ---------------------  |

20.04.2016
by Vatroslav Srziæ
*/

class OnOffButton
{
public:
	OnOffButton(int buttonPort);

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
