#ifndef ___STRINGS___h
#define ___STRINGS___h

#include "WString.h"

//this->SetError(((String)"Illegal pin value " + digitalPin) + ". Only digital pins between 2 and 7 are allowed.");

class StringHelperClass
{
public:
	String GetIllegalDigitalPinValue(int illegalValue, int legalMin, int legalMax);

	String GetIllegalAnalogPinValue(int illegalValue, int legalMin, int legalMax);

private:
	char* Error_IllegalPinValue1 = "Illegal pin value ";

	char* Error_IllegalPinValue2 = ". Only ";

	char* Error_IllegalPinValue3Digital = "digital";

	char* Error_IllegalPinValue3Analog = "analog";

	char* Error_IllegalPinValue4 = " pins between ";

	char* Error_IllegalPinValue5 = " and ";

	char* Error_IllegalPinValue6 = " are allowed.";
};

extern StringHelperClass StringHelper;

#endif