#include <DFRobot_ICP10111.h>
#include "LsPinAssign.h"

class LagopusAir
{
private:
  float altitude;
public:
  LagopusAir();
  ~LagopusAir();
  typedef struct{
    const uint8_t HEADER = 0xF3;
    unsigned long program_time;
    float temp;
    float air_pressure_1;
    float air_pressure_2;
    float air_pressure_3;
    float air_pressure_4;
    float air_pressure_5;
  }airPressure;
  airPressure _air;
  airPressure* _airptr = &_air;
  DFRobot_ICP10111 icp;
  bool initAir();
  void updateAir(unsigned long millisTime);
  void serialOutput();
};

