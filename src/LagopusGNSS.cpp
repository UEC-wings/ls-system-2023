#include "LagopusGNSS.h"

LagopusGNSS::LagopusGNSS(/* args */)
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
  _gnss.latitude = myGNSS.getLatitude();
  _gnss.longitude = myGNSS.getLongitude();
  _gnss.altitude = myGNSS.getAltitude();
  _gnss.siv = myGNSS.getSIV();
}

void LagopusGNSS::serialOutput()
{
  Serial.println(_gnss.program_time);
  Serial.println(_gnss.latitude);
  Serial.println(_gnss.longitude);
  Serial.println(_gnss.altitude);
  Serial.println(_gnss.siv);
}