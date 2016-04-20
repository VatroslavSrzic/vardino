//
//
//

#include "ButtonOnOff.h"
#include "StringHelper.h"

ButtonOnOffClass::ButtonOnOffClass(int digitalPin)
{
	if (digitalPin < 2 || digitalPin > 7)
	{
		this->SetError(StringHelper.GetIllegalDigitalPinValue(digitalPin, 2, 7));
		return;
	}
	else
	{
		this->digitalPin = digitalPin;
		pinMode(this->digitalPin, INPUT);
	}
}

bool ButtonOnOffClass::IsOn()
{
	return this->GetOnOffState();
}

bool ButtonOnOffClass::IsOff()
{
	return !this->GetOnOffState();
}

bool ButtonOnOffClass::GetOnOffState()
{
	int buttonState = 0;                // current state of the button
	static int lastButtonState = 0;     // previous state of the button
	static bool isON = false;           // (calculated) system state

	buttonState = digitalRead(this->digitalPin);

	if (buttonState != lastButtonState)
	{
		//button is released (similar to MouseUp)
		if (buttonState == LOW)
		{  // change the state and print it
		   //
			isON = !isON;
		}
	}

	lastButtonState = buttonState;

	return isON;
}