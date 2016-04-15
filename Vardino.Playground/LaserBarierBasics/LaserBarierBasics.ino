/*
  Photoresistor/laser basics
  http://linksprite.com/wiki/index.php5?title=Advanced_Sensors_Kit_for_Arduino
  
            | A1  -------signal--------S |  
  Arduino   | 5V  ---------------------  |  Photoresistor
            | GND ---------------------  |  
  
            | DD4 ---------------------S |
  Arduino   | 5V  ---------------------  |  Laser
            | GND ---------------------  |

  13.04.2016
  by Vatroslav Srziæ
 */

//GLOBALS
int PhotoresistorSenzor = A1;
int Laser = DD4;


// the setup function runs once when you press reset or power the board
void setup()
{
    pinMode(PhotoresistorSenzor, INPUT);

    pinMode(Laser, OUTPUT);

    Serial.begin(9600);
}

// the loop function runs over and over again forever
void loop() 
{
    static int loopCount = 0;
    loopCount++;

    static bool laserIsOn = false;

    if ((loopCount % 5) == 0)
    {
        if (laserIsOn)
        {
            digitalWrite(Laser, LOW);
            laserIsOn = false;
        }
        else
        {
            digitalWrite(Laser, HIGH);
            laserIsOn = true;
        }
    }
    
    int lightIntensity = analogRead(PhotoresistorSenzor);

    Serial.println(lightIntensity, DEC);
    delay(200);
}
