#include <SPI.h>
#include <Wire.h>
#include <SD.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>
#include <SparkFun_u-blox_GNSS_Arduino_Library.h>

#include "HardwareSerial.h"

#include "LsPinAssign.h"
#include "LsStateFlow.h"

#define BAUD_RATE 115200
#define DATALOG_FILE "datalog.txt"

SFE_UBLOX_GNSS myGNSS;
Adafruit_BNO055 bno = Adafruit_BNO055(55, 0x28, &Wire);
imu::Quaternion quat;

unsigned long program_time = 0;

typedef struct{
  const uint8_t HEADER = 0xF0;
  unsigned long program_time;
  float quat_w;
  float quat_x;
  float quat_y;
  float quat_z;
}quaternion;
quaternion _quat;


bool initImu(){
  Wire.setSCL(PIN_IMU_SCL);
  Wire.setSDA(PIN_IMU_SDA);
  Wire.begin();
  return bno.begin();
}

void updateImu(unsigned long millis_time){
  quat = bno.getQuat();
  _quat.program_time = millis_time;
  _quat.quat_w = quat.w();
  _quat.quat_x = quat.x();
  _quat.quat_y = quat.y();
  _quat.quat_z = quat.z();
}

void loggingImu(File dataFile){
  dataFile.print(_quat.HEADER);
  dataFile.print(_quat.program_time);
  dataFile.print(_quat.quat_x);
  dataFile.print(_quat.quat_x);
  dataFile.print(_quat.quat_y);
  dataFile.print(_quat.quat_z);
}

bool initSD(){
  SPI.setRX(PIN_SD_MISO);
  SPI.setTX(PIN_SD_MOSI);
  SPI.setSCK(PIN_SD_SCK);
  SPI.setCS(PIN_SD_CS);
  return SD.begin(PIN_SD_CS);
}

void setup() {
  Serial.begin(BAUD_RATE);
  Serial.println("System checking...");

  while(!initImu())Serial.println("IMU...");
  Serial.println("Imu connected");

  while(!initSD())Serial.println("SD...");
  Serial.println("SD connected");

}

void setup1(){
  delay(3000);
}

void loop() {
  program_time = millis();
  updateImu(program_time);
  delay(1000);
}

void loop1(){
  File dataFile = SD.open(DATALOG_FILE, FILE_WRITE);
    if (dataFile) {
      loggingImu(dataFile);
      dataFile.close();
  }
  else {
    Serial.println("error opening datalog.txt");
  }
  delay(1000);
}