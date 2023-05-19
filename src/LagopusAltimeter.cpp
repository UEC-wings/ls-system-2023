#include "LagopusAltimeter.h"

LagopusAltimeter::LagopusAltimeter(/* args */)
{
}

LagopusAltimeter::~LagopusAltimeter()
{
}

// ******ICP10111******

bool LagopusAltimeter::initAir()
{
  // begin、0の場合true,-1の場合falseを出力するようにライブラリを改変
  while(!icp.begin()){
    delay(100);
  }
  icp.setWorkPattern(icp.eNormal);
  return true;
}

void LagopusAltimeter::updateAir(unsigned long millsTime){
  alti.program_time = millsTime;
  alti.temp = icp.getTemperature();
  // 温度を取得するときに大気圧も取得しているのでその値をそのまま使う
  alti.air_pressure_1 = icp.getAirPressureFrom_t();
  alti.air_pressure_2 = icp.getAirPressure();
}

void LagopusAltimeter::serialAirPressureOutput()
{
  Serial.print(alti.HEADER);
  Serial.print(", ");
  Serial.print(alti.program_time);
  Serial.print(", ");
  Serial.print(alti.temp);
  Serial.print(", ");
  Serial.print(alti.air_pressure_1);
  Serial.print(", ");
  Serial.println(alti.air_pressure_2);
}

// ********************

// ******超音波センサ******

bool LagopusAltimeter::initUltrasonic(Stream &stream)
{
  delay(2000);
  ultrasonic.init(stream, PIN_RS485_CTRL);
  return true;
}

void LagopusAltimeter::updateUltrasonic(){
  ultrasonic.request(ULTRASONIC, REALTIME);
  if (ultrasonic.read() != -1){
    alti.height_1 = ultrasonic.dist;
  }
  ultrasonic.request(ULTRASONIC, REALTIME);
  if (ultrasonic.read() != -1){
    alti.height_2 = ultrasonic.dist;
  }
  ultrasonic.request(ULTRASONIC, REALTIME);
  if (ultrasonic.read() != -1){
    alti.height_3= ultrasonic.dist;
  }
}

void LagopusAltimeter::serialUltrasonicOutput(){
  Serial.print(alti.HEADER);
  Serial.print(", ");
  Serial.print(alti.program_time);
  Serial.print(", ");
  Serial.print(alti.height_1);
  Serial.print(", ");
  Serial.print(alti.height_2);
  Serial.print(", ");
  Serial.println(alti.height_3);
}
// ************************