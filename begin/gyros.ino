// INSTALL LIB ADAFRUIT
// Sketch > Include Library > Manage Libraries
// 
// HMC5883_Unifie

#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_HMC5883_U.h>
Adafruit_HMC5883_Unified mag = Adafruit_HMC5883_Unified(12345);
 
 
void setup(void) 
{
  Serial.begin(115200);
  Serial.println("");
  Serial.println("start");
  if(!mag.begin()) {
    Serial.println("Ooops, no HMC5883 detected ... Check your wiring!");
    while(1);
  }
}
 
void loop(void) 
{
  sensors_event_t event; 
  mag.getEvent(&event);
 
  float heading = atan2(event.magnetic.y, event.magnetic.x);
  float declinationAngle = 0.22;
  heading += declinationAngle;
 
  // Correct for when signs are reversed.
  if(heading < 0)
    heading += 2*PI;
 
  // Check for wrap due to addition of declination.
  if(heading > 2*PI)
    heading -= 2*PI;
 
  // Convert radians to degrees for readability.
  float headingDegrees = heading * 180/M_PI; 
 
  Serial.print("Heading (degrees): "); 
  Serial.println(headingDegrees);
 
  delay(100);
}
