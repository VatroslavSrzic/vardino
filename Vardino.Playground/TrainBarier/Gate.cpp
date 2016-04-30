//
//
//

#include <Servo.h>
#include "Gate.h"
#include "StringHelper.h"

GateClass::GateClass(int servoPin, int servoMinPulseWidth, int servoMaxPulseWidth, int closeDeg, int openDeg)
{
	if (servoPin > A7 || servoPin < A0)
	{
		this->SetError(StringHelper.GetIllegalAnalogPinValue(servoPin, A0, A7));
		return;
	}
	else
	{
		this->servoControlPin = servoPin;
	}

	if (servoMinPulseWidth < 500 || servoMinPulseWidth > 2499)
	{
		this->SetError(StringHelper.GetIllegalIntRange(servoMinPulseWidth, 500, 2499));
		return;
	}
	else
	{
		this->servoMinPulseWidth = servoMinPulseWidth;
	}

	if (servoMaxPulseWidth <= servoMinPulseWidth || servoMaxPulseWidth > 2500)
	{
		this->SetError(StringHelper.GetIllegalIntRange(servoMaxPulseWidth, servoMinPulseWidth, 2500));
		return;
	}
	else
	{
		this->servoMaxPulseWidth = servoMaxPulseWidth;
	}

	if (closeDeg <= 0 || closeDeg > 180)
	{
		this->SetError(StringHelper.GetIllegalIntRange(closeDeg, 0, 180));
		return;
	}
	else
	{
		this->closeDeg = closeDeg;
	}

	if (openDeg <= 0 || openDeg > 180)
	{
		this->SetError(StringHelper.GetIllegalIntRange(openDeg, 0, 180));
		return;
	}
	else
	{
		this->openDeg = openDeg;
	}
}

void GateClass::Open()
{
	if (!this->isInitialized)
	{
		this->SetError("Gate is not initialized");
		return;
	}

	servo.write(openDeg);
}

void GateClass::Close()
{
	if (!this->isInitialized)
	{
		this->SetError("Gate is not initialized");
		return;
	}

	servo.write(closeDeg);
}

void GateClass::Init()
{
	Attach();
	this->isInitialized = true;
}

bool GateClass::IsOpen()
{
	return servo.read() == openDeg;
}

bool GateClass::IsClose()
{
	return servo.read() == closeDeg;
}

bool GateClass::IsInitialized()
{
	return this->isInitialized;
}

void GateClass::Attach()
{
	this->servo.attach(servoControlPin, this->servoMinPulseWidth, this->servoMaxPulseWidth);

	// Turns out that this cute initialization procedure can do a lot of damage if there is no
	// room for the gate to move in that way.
	//for (size_t ms = this->servoMinPulseWidth; ms < this->servoMaxPulseWidth; ms = ms + 5)
	//{
	//	this->servo.writeMicroseconds(ms);
	//	delay(8);
	//}
	//
	//delay(1000);
	//
	//for (size_t ms = this->servoMaxPulseWidth; ms > this->servoMinPulseWidth; ms = ms - 10)
	//{
	//	this->servo.writeMicroseconds(ms);
	//	delay(10);
	//}

	this->servo.write(closeDeg);
}

void GateClass::Detach()
{
	// Turns out that this cute de-initialization procedure can do a lot of damage if there is
	// no room for the gate to move in that way.
	//int firstThird = (this->servoMaxPulseWidth + this->servoMinPulseWidth) / 3;
	//int secondThird = 2 * firstThird;
	//
	//for (size_t ms = this->servoMinPulseWidth; ms < firstThird; ms = ms + 20)
	//{
	//	this->servo.writeMicroseconds(ms);
	//	delay(15);
	//}
	//
	//delay(500);
	//
	//for (size_t ms = firstThird; ms < secondThird; ms = ms + 30)
	//{
	//	this->servo.writeMicroseconds(ms);
	//	delay(15);
	//}
	//
	//delay(750);
	//
	//for (size_t ms = secondThird; ms > this->servoMinPulseWidth; ms = ms - 40)
	//{
	//	this->servo.writeMicroseconds(ms);
	//	delay(10);
	//}

	this->servo.write(openDeg);
	this->servo.detach();
}