/*
uint8_t 符号なし1byte整数

データログのヘッダ
IMU     >> 0xF0
GNSS    >> 0xF1
AIR_SPEED >> 0xF2
AIR_PRESSURE >> 0xF3
ALTITUDE >> 0xF4
NRF52840 >> 0xF5

*/ 

const uint8_t FLAG_ON_IMU           =   (1 << 0); // 0000 0001
const uint8_t FLAG_ON_GNSS          =   (1 << 1); // 0000 0010
const uint8_t FLAG_ON_AIR_SPEED     =   (1 << 2); // 0000 0100
const uint8_t FLAG_ON_AIR_PRESSURE  =   (1 << 3); // 0000 1000
const uint8_t FLAG_ON_ALTITUDE      =   (1 << 4); // 0001 0000
const uint8_t FLAG_ON_NRF52849      =   (1 << 5); // 0010 0000
const uint8_t FLAG_ON_6             =   (1 << 6); // 0100 0000
const uint8_t FLAG_ON_7             =   (1 << 7); // 1000 0000

const uint8_t FLAG_OFF_IMU           =   (0 << 0);
const uint8_t FLAG_OFF_GNSS          =   (0 << 1);
const uint8_t FLAG_OFF_AIR_SPEED     =   (0 << 2);
const uint8_t FLAG_OFF_AIR_PRESSURE  =   (0 << 3);
const uint8_t FLAG_OFF_ALTITUDE      =   (0 << 4);
const uint8_t FLAG_OFF_NRF52849      =   (0 << 5);
const uint8_t FLAG_OFF_6             =   (0 << 6);
const uint8_t FLAG_OFF_7             =   (0 << 7);

uint8_t flagstate =     FLAG_ON_IMU
                    |   FLAG_ON_GNSS
                    |   FLAG_ON_AIR_SPEED
                    |   FLAG_ON_AIR_PRESSURE    
                    |   FLAG_ON_ALTITUDE
                    |   FLAG_ON_NRF52849        
                    |   FLAG_ON_6
                    |   FLAG_ON_7;
