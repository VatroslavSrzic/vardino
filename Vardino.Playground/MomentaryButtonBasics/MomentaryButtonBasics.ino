/*
  Momentary Button
			| DD3 -------signal--------S |
  Arduino   | 5V  ---------------------  |  Button
			| GND ---------------------  |

  16.04.2016
  by Vatroslav Srziæ
 */

 //GLOBALS
int Button = DD3;

// the setup function runs once when you press reset or power the board
void setup()
{
	pinMode(Button, INPUT);

	Serial.begin(9600);
}

// the loop function runs over and over again forever
void loop()
{
	Serial.print("The state is ");
	if (GetOnOffState(Button))
	{
		Serial.println("ON");
	}
	else
	{
		Serial.println("OFF");
	}

	delay(25);
}

bool GetOnOffState(int btn)
{
	int buttonState = 0;                // current state of the button
	static int lastButtonState = 0;     // previous state of the button
	static bool isON = false;           // (calculated) system state

	buttonState = digitalRead(btn);

	if (buttonState != lastButtonState)
	{
		//button is released (simmilar to MouseUp)
		if (buttonState == LOW)
		{  // change the state and print it
		   //
			isON = !isON;
		}
	}

	lastButtonState = buttonState;

	return isON;
}