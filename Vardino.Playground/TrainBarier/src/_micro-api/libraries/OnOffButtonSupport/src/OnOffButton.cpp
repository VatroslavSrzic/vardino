/*
Name:		OnOffButton.cpp
Created:	4/19/2016 10:36:17 PM
Author:	Vatro
Editor:	http://www.visualmicro.com
*/

#include "OnOffButton.h"

OnOffButton::OnOffButton(int digitalPin)
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

bool OnOffButton::InError()
{
	return this->inError;
}

String OnOffButton::GetErrorText()
{
	return this->errorText;
}

bool OnOffButton::IsOn()
{
	return this->GetOnOffState();
}

bool OnOffButton::IsOff()
{
	return !this->GetOnOffState();
}

void OnOffButton::ClearErrr()
{
	this->errorText = "";
	this->inError = false;
}

void OnOffButton::SetError(String errorText)
{
	this->errorText = errorText;
	this->inError = true;
}

bool OnOffButton::GetOnOffState()
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