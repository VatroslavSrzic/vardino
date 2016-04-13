/*
  Blink
  Inspired by http://www.instructables.com/id/Arduino-Nano-Infrared-Obstacle-Avoidance-Sensor-Wi/
  (4 pin version, ignoring enable pin)

  GND
  ______GND
  ______POW 5V
  ______SIG (digital) in this example will be on dig 2
  ______Enable
  EN

  10.04.2016
  by Vatroslav Srzi�
 */

//GLOBALS
int AvoidSensor = DD2;

// the setup function runs once when you press reset or power the board
void setup() 
{
    Serial.begin(9600);
}

// the loop function runs over and over again forever
void loop() 
{
    Serial.println(AvoidSensor); // print the data from the sensor
    delay(25);
}
