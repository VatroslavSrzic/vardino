//INCLUDES
#include <Servo.h>

#include "Gate.h"
#include "ErrorBase.h"
#include "LaserBeam.h"
#include "ButtonOnOff.h"
#include "ObstacleDetector.h"
#include "BarrierState.h"
/*
  Train barrier

  2016
  by Vatroslav Srziæ
 */

BarrierState CurrentState = Unknown;

GateClass Gate(A0, 572, 2278, 93, 170);
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
	delay(500);
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

	{	// Initialize gate or exit if failed
		//
		Serial.println("Initializing gate...");

		Gate.Init();
		if (Gate.InError())
		{
			ProcessFatalError("Error during gate initialization: ", Gate);
		}
		Serial.println("... ... gate initialized");
	}

	CurrentState = Off;
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
		if (BtnOnOff.IsOn())
		{
			Transition_From_Off_to_On();
		}
		break;

	case OnAndClosed:
		if (BtnOnOff.IsOff())
		{
			Transition_From_On_to_Off();
		}

		mustOpen = (ObstacleDetector.ObstacleDetected() || LaserBeam.IsCuttOff());
		if (mustOpen)
		{
			Transition_From_OnAndClosed_to_OnAndOpen();
		}
		break;

	case OnAndOpen:
		shouldClose = (!ObstacleDetector.ObstacleDetected() && !LaserBeam.IsCuttOff());
		if (shouldClose)
		{
			Transition_From_OnAndOpen_to_OnAndClosed();
		}
		break;

	default:
		Serial.print("Unsupported value of current state in the 'loop': ");
		Serial.println(CurrentState);
		delay(100);
		CurrentState = InError;
		break;
	}

	delay(50);
}

/* begin of transitions */

void Transition_From_Off_to_On()
{
	bool mustBeOpen = (ObstacleDetector.ObstacleDetected() || LaserBeam.IsCuttOff());

	if (mustBeOpen)
	{
		Gate.Open();
		CurrentState = OnAndOpen;
	}
	else
	{
		Gate.Close();
		CurrentState = OnAndClosed;
	}
}

void Transition_From_OnAndClosed_to_OnAndOpen()
{
	Gate.Open();

	CurrentState = OnAndOpen;
}

void Transition_From_OnAndOpen_to_OnAndClosed()
{
	Gate.Close();

	CurrentState = OnAndClosed;
}

void Transition_From_On_to_Off()
{
	Gate.Open();
	CurrentState = Off;
}

/* end of transitions */

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