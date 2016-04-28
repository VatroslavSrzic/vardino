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

	if (laserPin > 7 || laserPin < 2)
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

void LaserBeamClass::Calibrate(bool stayOn /*= true*/)
{
	this->isCalibrated = false;

	int totalLoopCount = 120;		// effectively this means that we
	int onOffLoopCountModulo = 20;	// will run this calibration for 6 seconds and
	int loopDelayMiliseconds = 50;	// will turn laser on/off 6 times (each second).

	for (int loopCount = 0; loopCount < totalLoopCount; loopCount++)
	{
		// toggle every second between on/off of laser
		if ((loopCount % onOffLoopCountModulo) == 0)
		{
			if (this->laserIsOn)
			{
				TurnLaserOff();
			}
			else
			{
				TurnLaserOn();
			}
		}

		//get the intensity
		int measuredResistance = GetResistanceReading();

		if (this->laserIsOn)
		{
			if ((this->highestResistanceWhenOn == -1) || (this->highestResistanceWhenOn < measuredResistance))
			{
				this->highestResistanceWhenOn = measuredResistance;
			}
		}
		else //the laser is off
		{
			if ((this->lowestResistanceWhenOff == -1) || (this->lowestResistanceWhenOff > measuredResistance))
			{
				this->lowestResistanceWhenOff = measuredResistance;
			}
		}

		//Serial.println(measuredResistance, DEC);

		//wait for the next loop
		delay(loopDelayMiliseconds);
	}

	this->isCalibrated = true;

	if (stayOn)
	{
		this->isRunning = true;
		if (!this->laserIsOn)
		{
			TurnLaserOn();
		}
	}
	else
	{
		this->isRunning = false;
		if (this->laserIsOn)
		{
			TurnLaserOff();
		}
	}

	Serial.print("Laser beam barrier is calibrated. ");
	Serial.print("Lowest Resistance When Off: ");
	Serial.print(this->lowestResistanceWhenOff, DEC);
	Serial.print(" Highest Resistance When On: ");
	Serial.print(this->highestResistanceWhenOn, DEC);
	Serial.println();
	Serial.print("The laser beam barrier is ");
	if (this->isRunning)
	{
		Serial.println("ON.");
	}
	else
	{
		Serial.println("OFF.");
	}
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
	if (!this->isCalibrated)
	{
		this->SetError("Laser beam barrier needs to be calibrated first.");
		return false;
	}

	if (!this->isRunning)
	{
		if (!this->laserIsOn)
		{
			TurnLaserOn();
		}
		this->isRunning = true;
	}

	return true;
}

bool LaserBeamClass::Stop()
{
	if (this->isRunning)
	{
		if (this->laserIsOn)
		{
			TurnLaserOff();
		}
		this->isRunning = false;
	}

	return true;
}

bool LaserBeamClass::IsCuttOff()
{
	if (!this->isRunning)
	{
		this->SetError("Laser beam barrier is not running.");
		return false;
	}
	else if (!this->isCalibrated)
	{
		this->SetError("Laser beam barrier needs to be calibrated first.");
		return false;
	}

	int resistanceReding = GetResistanceReading();

	if (resistanceReding > this->lowestResistanceWhenOff)
	{
		return true;
	}
	else if (resistanceReding < this->highestResistanceWhenOn)
	{
		return false;
	}
	else
	{
		Serial.print("Inconclusive resistance reading: ");
		Serial.println(resistanceReding, DEC);

		return false;
	}
}

void LaserBeamClass::TurnLaserOn()
{
	digitalWrite(this->laserPin, HIGH);
	delay(10);

	this->laserIsOn = true;
}

void LaserBeamClass::TurnLaserOff()
{
	digitalWrite(this->laserPin, LOW);
	delay(10);

	this->laserIsOn = false;
}

int LaserBeamClass::GetResistanceReading()
{
	return analogRead(this->photoresistorPin);
}