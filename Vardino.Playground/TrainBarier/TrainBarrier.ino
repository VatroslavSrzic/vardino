//INCLUDES
#include "ErrorBase.h"
#include "LaserBeam.h"
#include "ButtonOnOff.h"
#include "ObstacleDetector.h"

/*
  Train barrier

  2016
  by Vatroslav Srziæ
 */

ButtonOnOffClass BtnOnOff(3);
LaserBeamClass LaserBeam(A1, 4);
ObstacleDetectorClass ObstacleDetector(2);

void ProcessFatalError(const char * mainErrorMessage, ErrorBaseClass &errorObject)
{
	Serial.println(mainErrorMessage);
	Serial.print("      '");
	Serial.print(errorObject.GetErrorText());
	Serial.println("'");

	Serial.println("This is fatal. Exiting.");

	// so that errors can be printed out
	delay(500);
	exit(0);
}

// the setup function runs once when you press reset or power the board
void setup()
{
	Serial.begin(9600);

	CheckConfiguration();

	{	// Set up laser beam or exit if failed
		//
		Serial.println("Calibrating leaser beam...");

		LaserBeam.Calibrate(true);
		if (LaserBeam.InError())
		{
			ProcessFatalError("Error during calibration of leaser beam: ", LaserBeam);
		}
		Serial.println("... ... leaser beam calibrated");
	}
}

// the loop function runs over and over again forever
void loop()
{
	if (ObstacleDetector.ObstacleDetected())
	{
		Serial.println("obstacle");
	}
	else
	{
		Serial.println("clear");
	}

	delay(200);
}

void CheckConfiguration()
{
	if (BtnOnOff.InError())
	{
		ProcessFatalError("ON/OFF button is misconfigured: ", BtnOnOff);
	}

	if (LaserBeam.InError())
	{
		ProcessFatalError("Laser barrier is misconfigured: ", LaserBeam);
	}

	if (ObstacleDetector.InError())
	{
		ProcessFatalError("Obstacle Detector is misconfigured: ", ObstacleDetector);
	}
}