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
  _air.air_pressure_1 = icp.getAirPressureFrom_t();
  _air.air_pressure_2 = icp.getAirPressure();
  _air.air_pressure_3 = icp.getAirPressure();
  _air.air_pressure_4 = icp.getAirPressure();
  _air.air_pressure_5 = icp.getAirPressure();
}

void LagopusAir::serialOutput()
{
  Serial.print(_air.HEADER);
  Serial.println(_air.program_time);
  Serial.println(_air.temp);
  Serial.println(_air.air_pressure_1);
  Serial.println(_air.air_pressure_2);
  Serial.println(_air.air_pressure_3);
  Serial.println(_air.air_pressure_4);
  Serial.println(_air.air_pressure_5);
}
