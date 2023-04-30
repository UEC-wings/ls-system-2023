#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>
#include "LsPinAssign.h"

class LagopusImu
{
private:
  Adafruit_BNO055 bno = Adafruit_BNO055(55, 0x28, &Wire);
  imu::Quaternion quat;
  sensors_event_t angVelocityData, linearAccelData, magnetometerData;

public:
  LagopusImu();
  ~LagopusImu();
  bool initImu();
 
  void updateImu(unsigned long millisTime);
  void updateQuatMag();
  
  void serialOutputQuatMag();
  void serialOutputAccGyro();

  typedef struct
  {
    const uint8_t HEADER = 0xF0;
    float quat_w;
    float quat_x;
    float quat_y;
    float quat_z;
    float mag_x;
    float mag_y;
    float mag_z;
  }quatmag;
  quatmag _quatmag;
  quatmag* _quatmagptr = &_quatmag;
  
  typedef struct 
  {
    const uint8_t HEADER = 0xF6;
    unsigned long program_time;
    float acc_x;
    float acc_y;
    float acc_z;
    float gyro_x;
    float gyro_y;
    float gyro_z;
  }accgyro;
  accgyro _accgyro;
  accgyro* _accgyroptr = &_accgyro;

};
