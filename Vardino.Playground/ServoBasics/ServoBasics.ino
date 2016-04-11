/*
  Inspired by http://playground.arduino.cc/Learning/SingleServoExample
  but we are using Visual Studio bilt-in library from Michael Margolis

  10.04.2016
  by Vatroslav Srziæ
 */

//INCLUDES
#include <Servo.h>


//GLOBALS
int ServoMinPulseWidth = 572;
int ServoMaxPulseWidth = 2278;

Servo servo;
int servoControlPin = 14; //analog pin 0

// the setup function runs once when you press reset or power the board
void setup() 
{
	pinMode(1, OUTPUT);
	servoAttach(servo);

	Serial.begin(19200);
	Serial.println("Ready");
}

// the loop function runs over and over again forever
void loop() 
{
	static int v = 0;

	if (Serial.available()) 
	{
		char ch = Serial.read();

		switch (ch) 
		{
			case '0'...'9':
				v = v * 10 + ch - '0';
				if (v > 180)
				{
					v = v % 180;
				}
				Serial.print("Current v: "); Serial.println(v);
				break;
			case 's':
				Serial.print("Sending to servo: "); Serial.print(v); Serial.print(" [deg]"); Serial.println();
				servo.write(v);
				v = 0;
				break;
			case 'd':
				servoDetach(servo);
				break;
			case 'a':
				servoAttach(servo);
				break;
			case 'r':
				v = 0;
				servo.write(v);
				break;
			default:
				Serial.println("INVALID input");
		}
	}
}


void servoAttach(Servo s)
{
	s.attach(servoControlPin, ServoMinPulseWidth, ServoMaxPulseWidth);
	for (size_t ms = ServoMinPulseWidth; ms < ServoMaxPulseWidth; ms = ms+5)
	{
		s.writeMicroseconds(ms);
		delay(8);
	}

	delay(1000);

	for (size_t ms = ServoMaxPulseWidth; ms > ServoMinPulseWidth; ms=ms-10)
	{
		s.writeMicroseconds(ms);
		delay(10);
	}

	s.write(0);
}


void servoDetach(Servo s)
{
	int firstThird = (ServoMaxPulseWidth + ServoMinPulseWidth) / 3;
	int secondThird = 2 * firstThird;

	for (size_t ms = ServoMinPulseWidth; ms < firstThird; ms = ms + 20)
	{
		s.writeMicroseconds(ms);
		delay(15);
	}

	delay(500);

	for (size_t ms = firstThird; ms < secondThird; ms = ms + 30)
	{
		s.writeMicroseconds(ms);
		delay(15);
	}

	delay(750);

	for (size_t ms = secondThird; ms > ServoMinPulseWidth; ms = ms - 40)
	{
		s.writeMicroseconds(ms);
		delay(10);
	}

	s.write(0);
	s.detach();
}
