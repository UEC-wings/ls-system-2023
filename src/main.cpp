#include <SPI.h>
#include <Wire.h>
#include <SD.h>


#include <ArduinoQueue.h>
#include "HardwareSerial.h"

#include "LagopusImu.h"
#include "LagopusGNSS.h"
#include "LagopusAir.h"
#include "LsPinAssign.h"
#include "LsStateFlow.h"

#define BAUD_RATE 115200
#define DATALOG_FILE "datalog.bin"

#define QUEUE_SIZE_ITEMS 10
#define QUEUE_SIZE_BYTES 10

// Queue creation:
ArduinoQueue<byte*> dataQueue(QUEUE_SIZE_ITEMS);


LagopusImu LsImu;
LagopusGNSS LsGNSS;
LagopusAir LsAir;


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

  Wire.setSCL(PIN_IMU_SCL);
  Wire.setSDA(PIN_IMU_SDA);
  Wire.begin();
  delay(1000);
  Wire1.setSCL(PIN_GNSS_AIR_SCL);
  Wire1.setSDA(PIN_GNSS_AIR_SDA);
  Wire1.begin();
  delay(1000);
  while(!LsImu.initImu())Serial.println("IMU...");
  Serial.println("Imu connected");

  while(!LsGNSS.initGNSS())Serial.println("GNSS...");
  Serial.println("GNSS connected");
  delay(1000);
  //while(!LsAir.initAir())Serial.println("AirSensor...");
  //Serial.println("AirSensor connected");

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
  byte* data = (byte*)LsImu._quatptr;
  
  dataQueue.enqueue(data);

  Serial.println(LsImu._quat.quat_x);
  Serial.println(LsAir.icp.getAirPressure());
  LsGNSS.myGNSS.getDOP();
  delay(1000);
}

void loop1()
{
  File dataFile = SD.open(DATALOG_FILE, FILE_WRITE);
  if (dataFile && !dataQueue.isEmpty()) {
      int queueSize = dataQueue.itemCount();
      Serial.println(queueSize);
      for (int i = 0; i < queueSize; i++){
        byte* val = dataQueue.dequeue();
        size_t dataSize = sizeof(LsImu._quat);
        dataFile.write(val, dataSize);
      }
      dataFile.close();
  }
  else {
    Serial.println("error opening datalog.txt");
  }
  delay(1000);
}