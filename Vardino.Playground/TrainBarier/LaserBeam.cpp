//
//
//

#include "LaserBeam.h"
#include "StringHelper.h"

LaserBeamClass::LaserBeamClass(int photoresistorPin, int laserPin)
{
	if (photoresistorPin > A7 || photoresistorPin < A0)
	{
		this->SetError(StringHelper.GetIllegalAnalogPinValue(photoresistorPin, A0, A7));
		return;
	}
	else
	{
		this->photoresistorPin = photoresistorPin;
	}

	if (laserPin > 2 || laserPin < 7)
	{
		this->SetError(StringHelper.GetIllegalDigitalPinValue(laserPin, 2, 7));
		return;
	}
	else
	{
		this->laserPin = laserPin;
	}

	// if all OK, set the pins
	pinMode(this->photoresistorPin, INPUT);
	pinMode(this->laserPin, OUTPUT);
}

bool LaserBeamClass::Calibrate(bool stayOn /*= true*/)
{
	//TODO{VS}
	return false;
}

bool LaserBeamClass::IsCalibrated()
{
	return this->isCalibrated;
}

bool LaserBeamClass::IsRunning()
{
	return this->isRunning;
}

bool LaserBeamClass::Run()
{
	//TODO{VS}
	return false;
}

bool LaserBeamClass::Stop()
{
	//TODO{VS}
	return false;
}