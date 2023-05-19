#include <SparkFun_u-blox_GNSS_Arduino_Library.h>
#include "LsPinAssign.h"

class LagopusGNSS
{
private:
  
public:
  LagopusGNSS(/* args */);
  ~LagopusGNSS();
  typedef struct{
    const uint8_t HEADER = 0xF1;
    unsigned long program_time;
    uint32_t unixEpoch;
    long latitude;
    long longitude;
    long altitude;
    long groundSpeed;
    long heading;
  }gnss;
  gnss _gnss;
  gnss* _gnssptr = &_gnss;
  bool initGNSS();
  void updateGNSS(unsigned long millisTime);
  void serialOutput();
  SFE_UBLOX_GNSS myGNSS;
};

