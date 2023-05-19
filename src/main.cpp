#include <SPI.h>
#include <Wire.h>
#include <SD.h>
#include "HardwareSerial.h"

#include <ArduinoQueue.h>

// 音声再生クラス
#include "utils/NuttX.h"

// センサークラス
#include "LagopusImu.h"
#include "LagopusGNSS.h"
#include "LagopusAltimeter.h"
#include "LsPinAssign.h"
#include "LsStateFlow.h"

#define BAUD_RATE 115200
#define SERIALPIO_BAUD_RATE 9600 
#define DATALOG_FILE "datalog1.bin"

#define QUEUE_SIZE_ITEMS 3

// データログ用のQueue
ArduinoQueue<byte*> dataQueue(QUEUE_SIZE_ITEMS);

// 音声再生クラス
NuttX Audio;

// 自作クラス
LagopusImu LsImu;
LagopusGNSS LsGNSS;
LagopusAltimeter LsAlti;

// RS485超音波センサ
SerialPIO mySerial(PIN_RS485_TXPIO0, PIN_RS485_RXPIO0);

// プログラム内の時間
unsigned long program_time = 0;

// センサーログ構造体は32byte固定
const size_t PAYLOAD_SIZE = (sizeof(float) * 8);

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
  Serial.begin(BAUD_RATE);
  delay(1000);
  Serial.println("System checking...");
  mySerial.begin(SERIALPIO_BAUD_RATE);
  delay(2000);
  
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
  delay(100);
  while(!LsGNSS.initGNSS())Serial.println("GNSS...");
  Serial.println("GNSS connected");
  delay(100);
  while(!LsAlti.initAir())Serial.println("AirSensor...");
  Serial.println("AirSensor connected");
  delay(100);
  while(!LsAlti.initUltrasonic(mySerial))Serial.println("Ultrasonic...");
  Serial.println("Ultrasonic connectted");
  delay(100);
  while(!initSD())Serial.println("SD...");
  Serial.println("SD connected");
  delay(100);
}

void setup1()
{
  /*
  すべてのセンサーの初期化が終わり次第loop1のロガー状態に入る
  ビットフラグを用いてセンサーの初期化を確認
  */
  
  Serial1.begin(115200);
  while (!Serial1);
  Audio.init(Serial1);
  Serial.println("setup1 close");
  delay(3000);
}

void loop()
{
  LsImu.updateImu(millis());

  byte* dataAccGyro = (byte*)LsImu._accgyroptr;
  dataQueue.enqueue(dataAccGyro);
  
  byte* dataQuatMag = (byte*)LsImu._quatmagptr;
  dataQueue.enqueue(dataQuatMag);

  LsImu.serialOutputQuatMag();
  LsImu.serialOutputAccGyro();
  
  LsGNSS.updateGNSS(millis());
  byte* dataGnss = (byte*)LsGNSS._gnssptr;
  dataQueue.enqueue(dataGnss);

  LsGNSS.serialOutput();
  
  LsAlti.updateAir(millis());
  LsAlti.serialAirPressureOutput();


  LsAlti.updateUltrasonic();
  LsAlti.serialUltrasonicOutput();


  byte* dataAlti = (byte*)LsAlti.altiptr;
  dataQueue.enqueue(dataAlti);

  delay(300);
}

void loop1()
{
  File dataFile = SD.open(DATALOG_FILE, FILE_WRITE);
  if (dataFile && !dataQueue.isEmpty()) 
  {
      int queueSize = dataQueue.itemCount();
      Serial.println(queueSize);
      for (int i = 0; i < queueSize; i++)
      {
        byte* val = dataQueue.dequeue();
        Serial.print("datasize>>");
        Serial.println(PAYLOAD_SIZE);
        dataFile.write(val, PAYLOAD_SIZE);
      }
      dataFile.close();
  }

  /*
  NutStatus nutStatus = Audio.play("2022_1.wav");
  if(nutStatus == NUTTX_BUSY)
  {
    Serial.println("NUTTX_BUSY");
  } else
  {
    Serial.println("NUTTX_PLAY");
  }

  */

  delay(500);

}