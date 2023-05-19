#include <DFRobot_ICP10111.h>
#include "utils/RS485.h"
#include "LsPinAssign.h"

class LagopusAltimeter
{
private:
  float altitude;
  RS485 ultrasonic;
public:
  LagopusAltimeter();
  ~LagopusAltimeter();

  /* データロガー用構造体、固定32byte
   * Header
   * マイコン内の時間
   * 超音波センサ値 * 3
   * 大気圧値 * 2 
  */
  typedef struct{
    const uint8_t HEADER = 0xF3;
    unsigned long program_time;
    float temp;
    long height_1;
    long height_2;
    long height_3;
    float air_pressure_1;
    float air_pressure_2;
  }Altimeter;
  Altimeter alti;
  Altimeter* altiptr = &alti;

  // ******ICP10111******
  DFRobot_ICP10111 icp;
  bool initAir();
  void updateAir(unsigned long millisTime);
  void serialAirPressureOutput();
  // ********************

  // ******超音波センサ******
  bool initUltrasonic(Stream &stream);
  void updateUltrasonic();
  void serialUltrasonicOutput();
  // ************************
};

