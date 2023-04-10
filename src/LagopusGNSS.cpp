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