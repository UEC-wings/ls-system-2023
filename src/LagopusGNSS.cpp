#include "LagopusGNSS.h"

LagopusGNSS::LagopusGNSS()
{
}

LagopusGNSS::~LagopusGNSS()
{
}
bool LagopusGNSS::initGNSS()
{
  return myGNSS.begin(Wire1);
}

void LagopusGNSS::updateGNSS(unsigned long millisTime)
{
  _gnss.program_time = millisTime;
  _gnss.unixEpoch = myGNSS.getUnixEpoch();
  _gnss.latitude = myGNSS.getLatitude();
  _gnss.longitude = myGNSS.getLongitude();
  _gnss.altitude = myGNSS.getAltitudeMSL();
  _gnss.groundSpeed = myGNSS.getGroundSpeed();
  _gnss.heading = myGNSS.getHeading();
}

void LagopusGNSS::serialOutput()
{
  Serial.printf("gps,%d,%d,%d,%d,%d\n", _gnss.latitude, _gnss.longitude, _gnss.altitude, _gnss.groundSpeed, _gnss.heading);
}