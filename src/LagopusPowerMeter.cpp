#include "LagopusPowerMeter.h"

LagopusPowerMeter::LagopusPowerMeter(/* args */)
{
}

LagopusPowerMeter::~LagopusPowerMeter()
{
}
bool LagopusPowerMeter::initPower()
{
    Serial2.setTX(PIN_XIAO_TX1);
    Serial2.setRX(PIN_XIAO_RX1);
    Serial2.begin(115200);
    xiao.init(Serial2);
    return true;
}

void LagopusPowerMeter::updatePower(unsigned long millisTime)
{
  xiao.update();
  //delay(500);
  _power.program_time = millisTime;
  _power.cadence = xiao.getCadence();
  _power.power = xiao.getPowerAvg();
  _power.airSpeed = xiao.getAirSpeed();
  Serial.println(xiao.getPowerMeterBat());
}

void LagopusPowerMeter::serialPowerOutput()
{
    Serial.printf("cadence,%d,%d,%f\n", _power.cadence, _power.power, _power.airSpeed);
}
