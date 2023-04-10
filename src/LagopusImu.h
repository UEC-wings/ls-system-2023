#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>
#define PIN_IMU_SDA 16
#define PIN_IMU_SCL 17



class LagopusImu
{
private:
  Adafruit_BNO055 bno = Adafruit_BNO055(55, 0x28, &Wire);
  imu::Quaternion quat;

public:
  LagopusImu();
  ~LagopusImu();
  bool initImu();
  void updateImu(unsigned long millsTime);
  void serialDebug();
  typedef struct{
    const uint8_t HEADER = 0xF0;
    unsigned long program_time;
    float quat_w;
    float quat_x;
    float quat_y;
    float quat_z;
  }quaternion;
  quaternion _quat;
  quaternion* _quatptr = &_quat;
  
};
