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
  _gnss.groundSpeed = myGNSS.getGroundSpeed();
  _gnss.heading = myGNSS.getHeading();
}

void LagopusGNSS::serialOutput()
{
  /*
  Serial.print("gps");
  Serial.print(",");
  //Serial.print(_gnss.program_time);
  //Serial.print(",");
  //Serial.print(_gnss.unixEpoch);
  //Serial.print(",");
  Serial.print(_gnss.latitude);
  Serial.print(",");
  Serial.print(_gnss.longitude);
  Serial.print(",");
  Serial.print(_gnss.altitude);
  Serial.print(",");
  Serial.print(_gnss.groundSpeed);
  Serial.print(",");
  Serial.println(_gnss.heading);
  */
  Serial.printf("gps,%d,%d,%d,%d,%d\n", _gnss.latitude, _gnss.longitude, _gnss.altitude, _gnss.groundSpeed, _gnss.heading);
}