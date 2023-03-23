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

typedef struct{
  unsigned long program_time = 0;
  float quat_w = 1.0;
  float quat_x = 0.0;
  float quat_y = 0.0;
  float quat_z = 0.0;
}quaternion;
quaternion _quat;


bool InitImu(){
  Wire.setSCL(PIN_IMU_SCL);
  Wire.setSDA(PIN_IMU_SDA);
  Wire.begin();
  return bno.begin();
}

bool InitSD(){
  SPI.setRX(PIN_SD_MISO);
  SPI.setTX(PIN_SD_MOSI);
  SPI.setSCK(PIN_SD_SCK);
  SPI.setCS(PIN_SD_CS);
  return SD.begin(PIN_SD_CS);
}

void setup() {
  Serial.begin(BAUD_RATE);
  Serial.println("System checking...");

  while(!InitImu())Serial.println("IMU...");
  Serial.println("Imu connected");

  while(!InitSD())Serial.println("SD...");
  Serial.println("SD connected");

}

void setup1(){
  delay(3000);
}

void loop() {
  quat = bno.getQuat();
  _quat.program_time = millis();
  _quat.quat_w = quat.w();
  _quat.quat_x = quat.x();
  _quat.quat_y = quat.y();
  _quat.quat_z = quat.z();
  delay(1000);
}

void loop1(){
  File dataFile = SD.open(DATALOG_FILE, FILE_WRITE);
    if (dataFile) {
      dataFile.println(_quat.program_time);
      dataFile.println(_quat.quat_x);
      dataFile.println(_quat.quat_x);
      dataFile.println(_quat.quat_y);
      dataFile.println(_quat.quat_z);
      dataFile.close();
  }
  else {
    Serial.println("error opening datalog.txt");
  }
  delay(1000);
}