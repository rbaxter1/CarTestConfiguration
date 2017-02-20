#include <imu.h>
#include <Math.h>

float IMU::rad_factor;
float IMU::hardiron_x;
float IMU::hardiron_y;
float	IMU::hardiron_z;
float IMU::declination;

// references:
// http://cache.freescale.com/files/sensors/doc/app_note/AN4248.pdf
// https://www.pololu.com/file/download/LSM303DLH-compass-app-note.pdf?file_id=0J434
// https://gist.github.com/srlm-io/fafee8feed8bd5661266
// https://github.com/RoboSail/RoboSail/blob/master/Libraries/Orientation/Orientation.h
void IMU::calculate(float raw_accl_x, float raw_accl_y, float raw_accl_z,
                    float raw_magn_x, float raw_magn_y, float raw_magn_z,
                    float& heading, float& pitch, float& roll)
{
  float accl_x = -raw_accl_x;
  float accl_y = raw_accl_y;
  float accl_z = raw_accl_z;
  float magn_x = raw_magn_x - hardiron_x;
  float magn_y = raw_magn_y - hardiron_y;
  float magn_z = raw_magn_z - hardiron_z;

  magn_y = -magn_y;
  magn_z = -magn_z;
  
  roll = atan2(accl_y, accl_z);
  pitch = atan(-accl_x / sqrt( pow(accl_y,2) + pow(accl_z,2) ) );
  
  float magn_fy_fs = magn_z * sin(roll) - magn_y*cos(roll);
  float magn_fx_fs = magn_x * cos(pitch) + magn_y * sin(pitch) * sin(roll) + magn_z * sin(pitch) * cos(roll);
  
  float yaw = atan2(magn_fy_fs, magn_fx_fs);
  
  roll = roll * IMU::rad_factor;
  pitch = pitch * IMU::rad_factor;
  yaw = yaw * IMU::rad_factor;
  heading = yaw + declination;

  if (heading >= 360) {
    heading -= 360;
  } else if (heading < 0) {
    heading += 360;
  }
}

void IMU::configure(float in_declination, float in_hardiron_x,
                    float in_hardiron_y, float in_hardiron_z){
    declination = in_declination;
    hardiron_x = in_hardiron_x;
    hardiron_y = in_hardiron_y;
    hardiron_z = in_hardiron_z;
    IMU::rad_factor = 57.2957;
}
