#include "LagopusAir.h"

LagopusAir::LagopusAir(/* args */)
{
}

LagopusAir::~LagopusAir()
{
}

bool LagopusAir::initAir()
{
  // begin、0の場合true,-1の場合falseを出力するようにライブラリを改変
  while(!icp.begin()){
    delay(100);
  }
  icp.setWorkPattern(icp.eNormal);
  return true;
}

void LagopusAir::updateAir(unsigned long millsTime){
  _air.program_time = millsTime;
  _air.temp = icp.getTemperature();
  _air.air_pressure = icp.getAirPressure();
}

void LagopusAir::serialOutput()
{
  Serial.println(_air.program_time);
  Serial.println(_air.temp);
  Serial.println(_air.air_pressure);
}
