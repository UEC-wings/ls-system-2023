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

float LagopusAir::getAltitude()
{
  Wire1.beginTransmission(ADDR);
  altitude = icp.getElevation();
}