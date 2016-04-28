//
//
//

#include "ObstacleDetector.h"
#include "StringHelper.h"

ObstacleDetectorClass::ObstacleDetectorClass(int digitalPin)
{
	if (digitalPin > 7 || digitalPin < 2)
	{
		this->SetError(StringHelper.GetIllegalDigitalPinValue(digitalPin, 2, 7));
		return;
	}

	this->detectorPin = digitalPin;
}

bool ObstacleDetectorClass::ObstacleDetected()
{
	return (digitalRead(this->detectorPin) == 0);
}