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
  _gnss.unixEpoch = myGNSS.getUnixEpoch();
  _gnss.latitude = myGNSS.getLatitude();
  _gnss.longitude = myGNSS.getLongitude();
  _gnss.altitude = myGNSS.getAltitudeMSL();
  _gnss.pdop = myGNSS.getPDOP();
  _gnss.siv = myGNSS.getSIV();
}

void LagopusGNSS::serialOutput()
{
  Serial.print(_gnss.HEADER);
  Serial.print(", ");
  Serial.print(_gnss.program_time);
  Serial.print(", ");
  Serial.print(_gnss.unixEpoch);
  Serial.print(", ");
  Serial.print(_gnss.latitude);
  Serial.print(", ");
  Serial.print(_gnss.longitude);
  Serial.print(", ");
  Serial.print(_gnss.altitude);
  Serial.print(", ");
  Serial.print(_gnss.pdop);
  Serial.print(", ");
  Serial.println(_gnss.siv);
}