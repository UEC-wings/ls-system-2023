#include <DFRobot_ICP10111.h>


class LagopusAir
{
private:
  DFRobot_ICP10111 icp;
  float altitude;
  uint8_t ADDR = 0x63;
public:
  LagopusAir(/* args */);
  ~LagopusAir();
  bool initAir();
  float getAltitude();
};

