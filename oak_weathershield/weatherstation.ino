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

double humidity;
double temperature;
double pressure;
int ambient;

void printTemperature()
{
  temperature = htu.readTemperature();
}

void printHumidity()
{
  humidity = htu.readHumidity();
}

void printPressure()
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

void printAmbient()
{
  byte value0;
  Wire.beginTransmission(PCF8591); // wake up PCF8591
  Wire.write(ADC0); // control byte - read ADC0
  Wire.endTransmission(); // end tranmission
  Wire.requestFrom(PCF8591, 2);
  value0=Wire.read();
  value0=Wire.read();
  ambient = value0;
}

void setup() 
{
  htu.begin();
  if(!bmp.begin())
  {
    Particle.publish("Error, bmp not connected!");
    while(1);
  }
  Particle.variable("ambient", ambient);
  Particle.variable("temperature", temperature);
  Particle.variable("humidity", humidity);
  Particle.variable("pressure", pressure);
}

void loop() 
{
  printTemperature();
  printHumidity();
  printPressure();
  printAmbient();
  delay(30000);
}
