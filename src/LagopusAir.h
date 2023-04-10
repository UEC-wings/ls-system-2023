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
    float air_pressure;
  }airPressure;
  DFRobot_ICP10111 icp;
  bool initAir();
};

