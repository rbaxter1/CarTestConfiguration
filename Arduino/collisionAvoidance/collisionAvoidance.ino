#include <Wire.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_LSM9DS0.h>
#include <Adafruit_LSM303.h>
#include <Math.h>
#include <imu.h>
#include <lidar.h>
#include <move.h>

Adafruit_LSM303 lsmLIDAR = Adafruit_LSM303();
Adafruit_LSM9DS0 lsm = Adafruit_LSM9DS0();

void setup(void) 
{
  Serial.begin(9600);
  Serial.println("collision avoidance system"); 
  Serial.println("");

  // check this site for declination
  //http://www.ngdc.noaa.gov/geomag-web/#declination
  //Model Used:  WMM2015 Help
  //Latitude: 42° 18' 0" N
  //Longitude:  71° 18' 12" W
  //Date  Declination
  //2015-11-08  14° 40' W  ± 0° 22'  changing by  0° 4' E per year
  float declination = -14;
  
  // values from the calibration sequence
  float hardiron_x = -6.182;
  float hardiron_y = 4.636;
  float hardiron_z = -40.347;
  IMU::configure(declination, hardiron_x, hardiron_y, hardiron_z);
  
  if (!lsm.begin())
  {
    Serial.println("Oops ... unable to initialize the LSM9DS0. Check your wiring!");
    while (1);
  }
  Serial.println("Found LSM9DS0");

  if (!lsmLIDAR.begin())
  {
    Serial.println("Oops ... unable to initialize the LSM303. Check your wiring!");
    while (1);
  }
  Serial.println("Found LSM303");

  // wiring for motor shield
  const int enA = 5;
  const int in1 = 6;
  const int in2 = 7;
  const int enB = 2;
  const int in3 = 3;
  const int in4 = 4;
  MOVE::onSetup(enA, in1, in2, enB, in1, in2);		
}


float lidarHeading;
float lidarPitch;
float lidarRoll;

float carHeading;
float carPitch;
float carRoll;

int distanceReading = -1;

void loop(void) 
{ 
  lsmLIDAR.read();
  IMU::calculate(lsmLIDAR.accelData.x, lsmLIDAR.accelData.y, lsmLIDAR.accelData.z,
                 lsmLIDAR.magData.x, lsmLIDAR.magData.y, lsmLIDAR.magData.z,
                 lidarHeading, lidarPitch, lidarRoll);
  
  // lidar orientiation
  lsm.read();  
  IMU::calculate(lsm.accelData.x, lsm.accelData.y, lsm.accelData.z,
  		 lsm.magData.x, lsm.magData.y, lsm.magData.z,
  	         carHeading, carPitch, carRoll);

  // Get the LIDAR reading
  distanceReading = LIDAR::read();
                 
  Serial.print(lsmLIDAR.accelData.x);
  Serial.print(",");
  Serial.print(lsmLIDAR.accelData.y); 
  Serial.print(",");
  Serial.print(lsmLIDAR.accelData.z);
  Serial.print(",");
  Serial.print(lsmLIDAR.magData.x);
  Serial.print(",");
  Serial.print(lsmLIDAR.magData.y);
  Serial.print(",");
  Serial.print(lsmLIDAR.magData.z);
  Serial.print(",");

  Serial.print(lsm.accelData.x);
  Serial.print(",");
  Serial.print(lsm.accelData.y);
  Serial.print(",");
  Serial.print(lsm.accelData.z);
  Serial.print(",");
  Serial.print(lsm.magData.x);
  Serial.print(",");
  Serial.print(lsm.magData.y);
  Serial.print(",");
  Serial.print(lsm.magData.z);
  Serial.print(",");

  Serial.print(distanceReading);

  Serial.print(",");
  Serial.print(lidarHeading);
  Serial.print(",");
  Serial.print(lidarPitch);
  Serial.print(",");
  Serial.print(lidarRoll);
  Serial.print(",");
  Serial.print(carHeading);
  Serial.print(",");
  Serial.print(carPitch);
  Serial.print(",");
  Serial.print(carRoll);
  
  Serial.print("\n");
	
  // Act	
  if (distanceReading > -1)
  {
    if (distanceReading < 150)
    {
     	MOVE::kill();
    }
    else
    {
    	MOVE::setGear(true, 255);
    }
  }
}
