//
//
//

#include "StringHelper.h"

String StringHelperClass::GetIllegalDigitalPinValue(int illegalValue, int legalMin, int legalMax)
{
	return String() + this->Error_IllegalPinValue1 + illegalValue + this->Error_IllegalPinValue2 + this->Error_IllegalPinValue3Digital +
		this->Error_IllegalPinValue4 + legalMin + this->Error_IllegalPinValue5 + legalMax + this->Error_IllegalPinValue6;
}

String StringHelperClass::GetIllegalAnalogPinValue(int illegalValue, int legalMin, int legalMax)
{
	return String() + this->Error_IllegalPinValue1 + illegalValue + this->Error_IllegalPinValue2 + this->Error_IllegalPinValue3Analog +
		this->Error_IllegalPinValue4 + legalMin + this->Error_IllegalPinValue5 + legalMax + this->Error_IllegalPinValue6;
}

StringHelperClass StringHelper;