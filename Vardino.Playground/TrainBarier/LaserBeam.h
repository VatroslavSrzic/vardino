// LaserBeam.h

#ifndef _LASERBEAM_h
#define _LASERBEAM_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

#include "ErrorBase.h"

/*
			| A1   -------signal--------S |
  Arduino   | 5V   ---------------------  |  Photo-resistor
			| GND  ---------------------  |

			| DIG4 ---------------------S |
  Arduino   | 5V   ---------------------  |  Laser
			| GND  ---------------------  |

  20.04.2016
  by Vatroslav Srziæ
*/

class LaserBeamClass : public ErrorBaseClass
{
public:
	LaserBeamClass(int photoresistorPin, int laserPin);

	void Calibrate(bool stayOn = true);

	bool IsCalibrated();

	bool IsRunning();

	bool Run();

	bool Stop();

	bool IsCuttOff();

protected:
	int photoresistorPin = -1;
	int laserPin = -1;

	bool isCalibrated = false;
	bool isRunning = false;

	int highestResistanceWhenOn = -1;
	int lowestResistanceWhenOff = -1;

private:
	bool laserIsOn = false;

	void TurnLaserOn();
	void TurnLaserOff();
	int GetResistanceReading();
};

#endif
