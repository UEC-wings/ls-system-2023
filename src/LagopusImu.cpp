#include "LagopusImu.h"

LagopusImu::LagopusImu()
{

}

bool LagopusImu::initImu()
{
  return bno.begin();
}

void LagopusImu::updateImu(unsigned long millisTime){
  quat = bno.getQuat();
  bno.getEvent(&magnetometerData, Adafruit_BNO055::VECTOR_MAGNETOMETER);
  bno.getEvent(&linearAccelData, Adafruit_BNO055::VECTOR_LINEARACCEL);
  bno.getEvent(&angVelocityData, Adafruit_BNO055::VECTOR_GYROSCOPE);
  
  _accgyro.program_time = millisTime;
  _accgyro.acc_x = linearAccelData.acceleration.x;
  _accgyro.acc_y = linearAccelData.acceleration.y;
  _accgyro.acc_z = linearAccelData.acceleration.z;
  _accgyro.gyro_x = angVelocityData.gyro.x;
  _accgyro.gyro_y = angVelocityData.gyro.y;
  _accgyro.gyro_z = angVelocityData.gyro.z;

  _quatmag.quat_w = quat.w();
  _quatmag.quat_x = quat.x();
  _quatmag.quat_y = quat.y();
  _quatmag.quat_z = quat.z();
  _quatmag.mag_x = magnetometerData.magnetic.x;
  _quatmag.mag_y = magnetometerData.magnetic.y;
  _quatmag.mag_z = magnetometerData.magnetic.z;
}

void LagopusImu::updateQuatMag()
{
  quat = bno.getQuat();
  _quatmag.quat_w = quat.w();
  _quatmag.quat_x = quat.x();
  _quatmag.quat_y = quat.y();
  _quatmag.quat_z = quat.z();
  bno.getEvent(&magnetometerData, Adafruit_BNO055::VECTOR_MAGNETOMETER);
  _quatmag.mag_x = magnetometerData.magnetic.x;
  _quatmag.mag_y = magnetometerData.magnetic.y;
  _quatmag.mag_z = magnetometerData.magnetic.z;

}

void LagopusImu::updateAccGyro(unsigned long millsTime){
  _accgyro.program_time = millsTime;
  bno.getEvent(&linearAccelData, Adafruit_BNO055::VECTOR_LINEARACCEL);
  bno.getEvent(&angVelocityData, Adafruit_BNO055::VECTOR_GYROSCOPE);
  _accgyro.acc_x = linearAccelData.acceleration.x;
  _accgyro.acc_y = linearAccelData.acceleration.y;
  _accgyro.acc_z = linearAccelData.acceleration.z;
  _accgyro.gyro_x = angVelocityData.gyro.x;
  _accgyro.gyro_y = angVelocityData.gyro.y;
  _accgyro.gyro_z = angVelocityData.gyro.z;
}

void LagopusImu::serialOutputQuatMag()
{
  Serial.print(_quatmag.HEADER);
  Serial.print(_quatmag.quat_w);
  Serial.print(_quatmag.quat_x);
  Serial.print(_quatmag.quat_y);
  Serial.print(_quatmag.quat_z);
  Serial.print(_quatmag.mag_x);
  Serial.print(_quatmag.mag_y);
  Serial.println(_quatmag.mag_z);
}

void LagopusImu::serialOutputAccGyro()
{
  Serial.print(_accgyro.HEADER);
  Serial.print(_accgyro.program_time);
  Serial.print(_accgyro.acc_x);
  Serial.print(_accgyro.acc_y);
  Serial.print(_accgyro.acc_z);
  Serial.print(_accgyro.gyro_x);
  Serial.print(_accgyro.gyro_y);
  Serial.println(_accgyro.gyro_z);
}
