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
#include "LagopusPowerMeter.h"
#include "LsPinAssign.h"
#include "LsVoice.h"

#define BAUD_RATE 115200
#define SERIALPIO_BAUD_RATE 9600 
#define DATALOG_FILE "datalog.bin"

#define QUEUE_SIZE_ITEMS 10

// データログ用のQueue
ArduinoQueue<byte*> dataQueue(QUEUE_SIZE_ITEMS);

// 音声再生クラス
NuttX Audio;

// 自作クラス
LagopusImu LsImu;
LagopusGNSS LsGNSS;
LagopusAltimeter LsAlti;
LagopusPowerMeter LsPower;


// RS485超音波センサ
SerialPIO mySerial(PIN_RS485_TXPIO0, PIN_RS485_RXPIO0);

// プログラム内の時間
unsigned long program_time = 0;

// センサーログ構造体は32byte固定
const size_t PAYLOAD_SIZE = (sizeof(float) * 8);

// Androidに送るようのデータ
long lat;
long lon;
long head;
long height;
unsigned long ctl;
int cad;

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
  delay(500);
  
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
    while(!LsAlti.initControl())Serial.println("Ctl...");
  Serial.println("Control connectted");
  delay(100);
  while(!LsPower.initPower())Serial.println("Power...");
  Serial.println("PowerM connected");
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
  delay(10000);
  Serial1.begin(BAUD_RATE);
  while (!Serial1) Serial.println("eee");
  Audio.init(Serial1);
  delay(500);
  NutStatus nutStatus = Audio.play("2022_7.wav");
  Serial.print("ss");
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
  
  // androidに送る用
  lat = LsGNSS._gnss.latitude;
  lon = LsGNSS._gnss.longitude;
  head = LsGNSS._gnss.heading;
  
  dataQueue.enqueue(dataGnss);
  
  LsAlti.updateAirSensor(millis());
  
  byte* dataAlti = (byte*)LsAlti.altiptr;
  height = LsAlti.alti.height_1;
  ctl = LsAlti.alti.ctlValue;
  
  dataQueue.enqueue(dataAlti);

  LsPower.updatePower(millis());
  byte* dataPower = (byte*)LsPower._powerptr;
  cad = LsPower._power.cadence;
  dataQueue.enqueue(dataPower);

  Serial.printf("data,%d,%d,%d,%d,%ld,%d\n", lat, lon, head, height, ctl, cad);
}

void loop1()
{
  File dataFile = SD.open(DATALOG_FILE, FILE_WRITE);
  if (dataFile && !dataQueue.isEmpty()) 
  {
      int queueSize = dataQueue.itemCount();
      for (int i = 0; i < queueSize; i++)
      {
        byte* val = dataQueue.dequeue();
        dataFile.write(val, PAYLOAD_SIZE);
      }
      dataFile.close();
  }
   byte data_size = Serial.available();

  if (data_size > 0)
  {
    delay(20);
    data_size = Serial.available();
    byte buf[data_size];
    Serial.print(F("data_size "));
    Serial.println(data_size);
    for (byte i = 0; i < data_size; i++){
      buf[i] = Serial.read();
      Serial.print((char)buf[i]);
      pinMode(25, OUTPUT);
      digitalWrite(25, HIGH);
      delay(500);
      digitalWrite(25, LOW);
    }
    
    Serial.println();
  }

}