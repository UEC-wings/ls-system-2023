#include "LagopusImu.h"

LagopusImu::LagopusImu()
{

}

bool LagopusImu::initImu()
{
  return bno.begin();
}

void LagopusImu::updateImu(unsigned long millisTime)
{
  quat = bno.getQuat();
  _quat.program_time = millisTime;
  _quat.quat_w = quat.w();
  _quat.quat_x = quat.x();
  _quat.quat_y = quat.y();
  _quat.quat_z = quat.z();
}

void LagopusImu::serialDebug()
{
  Serial.print(_quat.program_time);
  Serial.print(_quat.quat_w);
  Serial.print(_quat.quat_x);
  Serial.print(_quat.quat_y);
  Serial.print(_quat.quat_z);
}
