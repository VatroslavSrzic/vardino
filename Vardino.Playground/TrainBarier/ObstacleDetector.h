// ObstacleDetector.h

#ifndef _OBSTACLEDETECTOR_h
#define _OBSTACLEDETECTOR_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

#include "ErrorBase.h"

/*

  GND  ______GND
	   ______POW 5V
	   ______SIG (digital)
	   ______Enable (ignored, meaning let it be always on)
  EN
*/

class ObstacleDetectorClass : public ErrorBaseClass
{
public:
	ObstacleDetectorClass(int digitalPin);

	bool ObstacleDetected();

protected:
	int detectorPin = -1;

private:
};

#endif
