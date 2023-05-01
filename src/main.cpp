#include <SPI.h>
#include <Wire.h>
#include <SD.h>
#include "HardwareSerial.h"

#include <ArduinoQueue.h>

// センサークラス
#include "utils/NuttX.h"
#include "utils/RS485.h"

// 自作クラス
#include "LagopusImu.h"
#include "LagopusGNSS.h"
#include "LagopusAir.h"
#include "LsPinAssign.h"
#include "LsStateFlow.h"

#define BAUD_RATE 115200
#define DATALOG_FILE "datalog1.bin"

#define QUEUE_SIZE_ITEMS 3

// Queue creation:
ArduinoQueue<byte*> dataQueue(QUEUE_SIZE_ITEMS);

// センサークラス
NuttX Audio;
RS485 Sensor;

// 自作クラス
LagopusImu LsImu;
LagopusGNSS LsGNSS;
LagopusAir LsAir;

// プログラム内の時間
unsigned long program_time = 0;

const size_t payload_size = (sizeof(float) * 8);

bool initSD()
{
  SPI.setRX(PIN_SD_MISO0);
  SPI.setTX(PIN_SD_MOSI0);
  SPI.setSCK(PIN_SD_SCK0);
  SPI.setCS(PIN_SD_CS0);
  return SD.begin(PIN_SD_CS0);
}

void setup() 
{
  delay(5000);
  Serial.begin(BAUD_RATE);
  Serial.println("System checking...");
  Wire.setSCL(PIN_IMU_AIR_SCL0);
  Wire.setSDA(PIN_IMU_AIR_SDA0);
  Wire.begin();
  delay(500);
  Wire1.setSCL(PIN_GNSS_SCL1);
  Wire1.setSDA(PIN_GNSS_SDA1);
  Wire1.begin();
  delay(500);

  while(!LsImu.initImu())Serial.println("IMU...");
  Serial.println("Imu connected");

  while(!LsGNSS.initGNSS())Serial.println("GNSS...");
  Serial.println("GNSS connected");

  while(!LsAir.initAir())Serial.println("AirSensor...");
  Serial.println("AirSensor connected");

  while(!initSD())Serial.println("SD...");
  Serial.println("SD connected");

}

void setup1()
{
  /*
  すべてのセンサーの初期化が終わり次第loop1のロガー状態に入る
  ビットフラグを用いてセンサーの初期化を確認
  */
  delay(3000);
}

void loop()
{
  LsImu.updateImu(millis());

  byte* dataAccGyro = (byte*)LsImu._accgyroptr;
  dataQueue.enqueue(dataAccGyro);
  
  byte* dataQuatMag = (byte*)LsImu._quatmagptr;
  dataQueue.enqueue(dataQuatMag);

  LsGNSS.updateGNSS(millis());
  byte* dataGnss = (byte*)LsGNSS._gnssptr;
  dataQueue.enqueue(dataGnss);
  
  LsAir.updateAir(millis());
  byte* dataAir = (byte*)LsAir._airptr;
  dataQueue.enqueue(dataAir);

  LsImu.serialOutputQuatMag();
  LsImu.serialOutputAccGyro();
  LsGNSS.serialOutput();
  LsAir.serialOutput();

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
        Serial.print("datasize>>");
        Serial.println(payload_size);
        dataFile.write(val, payload_size);
      }
      dataFile.close();
  }
  delay(1000);
}