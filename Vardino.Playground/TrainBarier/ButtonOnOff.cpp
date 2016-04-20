//
//
//

#include "ButtonOnOff.h"

ButtonOnOffClass::ButtonOnOffClass(int digitalPin)
{
	if (digitalPin < 2 || digitalPin > 7)
	{
		this->SetError(((String)"Illegal pin value " + digitalPin) + " Only pins between 2 and 7 are allowed.");
	}
	else
	{
		this->digitalPin = digitalPin;
		pinMode(this->digitalPin, INPUT);
	}
}

bool ButtonOnOffClass::InError()
{
	return this->inError;
}

String ButtonOnOffClass::GetErrorText()
{
	return this->errorText;
}

bool ButtonOnOffClass::IsOn()
{
	return this->GetOnOffState();
}

bool ButtonOnOffClass::IsOff()
{
	return !this->GetOnOffState();
}

void ButtonOnOffClass::ClearErrr()
{
	this->errorText = "";
	this->inError = false;
}

void ButtonOnOffClass::SetError(String errorText)
{
	this->errorText = errorText;
	this->inError = true;
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