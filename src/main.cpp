#include <SPI.h>
#include <Wire.h>
#include <SD.h>


#include <ArduinoQueue.h>
#include "HardwareSerial.h"

#include "LagopusImu.h"
#include "LagopusGNSS.h"
#include "LsPinAssign.h"
#include "LsStateFlow.h"

#define BAUD_RATE 115200
#define DATALOG_FILE "datalog.txt"


LagopusImu LsImu;
LagopusGNSS LsGNSS;


unsigned long program_time = 0;

bool initSD()
{
  SPI.setRX(PIN_SD_MISO);
  SPI.setTX(PIN_SD_MOSI);
  SPI.setSCK(PIN_SD_SCK);
  SPI.setCS(PIN_SD_CS);
  return SD.begin(PIN_SD_CS);
}

void setup() 
{
  delay(5000);
  Serial.begin(BAUD_RATE);
  Serial.println("System checking...");

  while(!LsImu.sensorInit())Serial.println("IMU...");
  Serial.println("Imu connected");

  bool b = LsGNSS.initGNSS();
  if (b){
    Serial.println("GNSS connected");
  }else{
    Serial.println("rgaer'gnhaer");
  }
  

  while(!initSD())Serial.println("SD...");
  Serial.println("SD connected");

}

void setup1()
{
  delay(3000);
}

void loop()
{
  program_time = millis();
  LsImu.updateImu(program_time);
  Serial.println("@@@@@@@@@@@@@");
  delay(1000);
}

void loop1()
{
  File dataFile = SD.open(DATALOG_FILE, FILE_WRITE);
    if (dataFile) {
      dataFile.close();
  }
  else {
    Serial.println("error opening datalog.txt");
  }
  delay(1000);
}