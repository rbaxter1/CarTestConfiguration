#ifndef IMU_h
#define IMU_h

class IMU {
 public:
 	
  static void calculate(float raw_accl_x, float raw_accl_y, float raw_accl_z,
												float raw_magn_x, float raw_magn_y, float raw_magn_z,
												float& heading, float& pitch, float& roll);

  static void configure(float declination, float hardiron_x, float hardiron_y,
  											float hardiron_z);

  static float declination;
  static float hardiron_x;
  static float hardiron_y;
  static float hardiron_z;
  static float rad_factor;
};

#endif