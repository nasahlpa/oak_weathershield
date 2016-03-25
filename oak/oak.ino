/*Oak Weather Shield sample code
 * Using SparkFunHTU21D.h library from https://github.com/sparkfun/SparkFun_HTU21D_Breakout_Arduino_Library
 * Using BMP180_Breakout_Arduino_Library from https://github.com/sparkfun/BMP180_Breakout_Arduino_Library
 *
 * Get temperature and humidity from HTU21D, pressure from BMP180 with I2C
 * Ambient light is read out with PCF8591 ADC on ADC0
 */

#include <Wire.h>
#include "SparkFunHTU21D.h"
#include "SFE_BMP180.h"

HTU21D htu;
SFE_BMP180 bmp;

#define ALTITUDE 509 //Altitude in meter
#define PCF8591 (0x90 >> 1) //I2C bus address
#define ADC0 0x00 //ADC0

int Sleep_pin = 5;   // (Configure as INPUT_PULLUP to default HIGH)
int OakLEDpin = 1;   // Oak onboard LED pin 1
int sleepTimeS = 150; // 150 seconds - adjust a needed

float temperature;
float humidity;
float pressure;
int ambient;

void fetchTemperature()
{
  temperature = htu.readTemperature();
}

void fetchHumidity()
{
  humidity = htu.readHumidity();
}

void fetchPressure()
{
  char status  = bmp.startTemperature();
  char buffer[10];
  double T,P,p0;
  if (status != 0)
  {
    delay(status);
    
    status = bmp.getTemperature(T);
    if (status != 0)
    {
      status = bmp.startPressure(3);
      if (status != 0)
      {
        delay(status);
        status = bmp.getPressure(P,T);
        if (status != 0)
        {
          pressure = bmp.sealevel(P,ALTITUDE);
        }
        else Particle.publish("error retrieving pressure measurement\n");
      }
      else Particle.publish("error starting pressure measurement\n");
    }
    else Particle.publish("error retrieving temperature measurement\n");
  }
  else Particle.publish("error starting temperature measurement\n");
}

void printData()
{
  char tmpStr[64];
  sprintf(tmpStr, "weather;%s;%s;%s;%s", String(temperature).c_str(), String(ambient).c_str(), String(pressure).c_str(), String(humidity).c_str());
  Particle.publish("weatherstation", tmpStr, 60, PRIVATE);
}

void fetchAmbient()
{
  byte value0;
  Wire.beginTransmission(PCF8591); // wake up PCF8591
  Wire.write(ADC0); // control byte - read ADC0
  Wire.endTransmission(); // end tranmission
  Wire.requestFrom(PCF8591, 2);
  value0 = Wire.read();
  value0 = Wire.read();
  delay(200);
  ambient = value0;
}

void setup(void)
{
  pinMode(Sleep_pin, INPUT_PULLUP); // Use pullup mode to default HIGH

  htu.begin();
  if (!bmp.begin())
  {
    Particle.publish("Error, bmp not connected!");
    while (1);
  }
  fetchTemperature();
  fetchHumidity();
  fetchPressure();
  fetchAmbient();
  printData();

  if (digitalRead(Sleep_pin) == HIGH) 
  {
    ESP.deepSleep(sleepTimeS * 1000000, WAKE_RF_DEFAULT); // Sleep
  }
} //END setup()

void loop(void)
{

}
