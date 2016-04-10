/*
  Line tracking
  Inspired by http://www.dfrobot.com/wiki/index.php/Line_Tracking_Sensor_for_Arduino_(SKU:SEN0017).

  10.04.2016
  by Vatroslav Srziæ
 */


// the setup function runs once when you press reset or power the board
void setup() 
{
	Serial.begin(9600);
}

// the loop function runs over and over again forever
void loop() 
{
	Serial.println(digitalRead(2)); // print the data from the sensor
	delay(500);
}
