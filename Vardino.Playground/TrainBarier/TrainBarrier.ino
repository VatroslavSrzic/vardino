//INCLUDES
#include "Gate.h"
#include "ErrorBase.h"
#include "LaserBeam.h"
#include "ButtonOnOff.h"
#include "ObstacleDetector.h"
#include "BarrierState.h"
#include "Gate.h"

/*
  Train barrier

  2016
  by Vatroslav Srziæ
 */

BarrierState CurrentState = Unknown;

GateClass Gate(A0);
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

	CurrentState = InError;

	// so that errors can be printed out
	delay(200);
}

// the setup function runs once when you press reset or power the board
void setup()
{
	CurrentState = Initializing;

	Serial.begin(9600);

	FastExitIfInError();

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
	FastExitIfInError();

	bool mustOpen = false;
	bool shouldClose = false;

	switch (CurrentState)
	{
	case Off:
		//nothing
		break;

	case OnAndClosed:
		mustOpen = (ObstacleDetector.ObstacleDetected() || LaserBeam.IsCuttOff());
		if (mustOpen)
		{
			//open the gate

			CurrentState = OnAndOpen;
		}
		break;

	case OnAndOpen:
		shouldClose = (!ObstacleDetector.ObstacleDetected() && !LaserBeam.IsCuttOff());
		if (shouldClose)
		{
			//close the gate

			CurrentState = OnAndClosed;
		}
		break;

	default:
		Serial.print("Unsupported value of current state in the 'loop': ");
		Serial.println(CurrentState);
		CurrentState = InError;
		break;
	}

	delay(50);
}

void FastExitIfInError()
{
	if (BtnOnOff.InError())
	{
		ProcessFatalError("ON/OFF button is in error: ", BtnOnOff);
	}

	if (LaserBeam.InError())
	{
		ProcessFatalError("Laser barrier is in error: ", LaserBeam);
	}

	if (ObstacleDetector.InError())
	{
		ProcessFatalError("Obstacle Detector is in error: ", ObstacleDetector);
	}

	if (Gate.InError())
	{
		ProcessFatalError("Gate is in error: ", Gate);
	}

	if (CurrentState == InError)
	{
		exit(0);
	}
}