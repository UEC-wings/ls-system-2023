#include <SparkFun_u-blox_GNSS_Arduino_Library.h>

#define PIN_GNSS_SDA 12
#define PIN_GNSS_SCL 13

class LagopusGNSS
{
private:
  SFE_UBLOX_GNSS myGNSS;
public:
  LagopusGNSS(/* args */);
  ~LagopusGNSS();
  bool initGNSS();
  
};

