#include "LagopusGNSS.h"

LagopusGNSS::LagopusGNSS(/* args */)
{
}

LagopusGNSS::~LagopusGNSS()
{
}
bool LagopusGNSS::initGNSS()
{
  Wire1.setSCL(PIN_GNSS_SCL);
  Wire1.setSDA(PIN_GNSS_SDA);
  Wire1.begin();
  return myGNSS.begin(Wire1);
}