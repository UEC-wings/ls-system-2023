/*
                                    Raspberry Pi Pico Pinout

UART_0_TX   I2C_0_SDA   SPI_0_RX    GP0    1|     |40   VBUS
UART_0_RX   I2C_0_SCL   SPI_0_CSn   GP1    2|     |39   VSYS
                                    GND    3|     |38   GND
            I2C_1_SDA   SPI_0_SCK   GP2    4|     |37   3V3_EN
            I2C_1_SCL   SPI_0_TX    GP3    5|     |36   3V3_OUT
UART_1_TX   I2C_0_SDA   SPI_0_RX    GP4    6|     |35          ADC_VREF
UART_1_RX   I2C_0_SCL   SPI_0_CSn   GP5    7|     |34   GP28   ADC26
                                    GND    8|     |33   GND    AGND
            I2C_1_SDA   SPI_0_SCK   GP6    9|     |32   GP27   ADC1       I2C_1_SCL
            I2C_1_SCL   SPI_0_TX    GP7   10|     |31   GP26   ADC0       I2C_1_SDA
UART_1_TX   I2C_0_SDA   SPI_1_RX    GP8   11|     |30   RUN
UART_1_RX   I2C_0_SCL   SPI_1_CSn   GP9   12|     |29   GP22
                                    GND   13|     |28   GND
            I2C_1_SDA   SPI_1_SCK   GP10  14|     |27   GP21              I2C_0_SCL
            I2C_1_SCL   SPI_1_TX    GP11  15|     |26   GP20              I2C_0_SDA
UART_0_TX   I2C_0_SDA   SPI_1_RX    GP12  16|     |25   GP19   SPI_0_TX   I2C_1_SCL
UART_0_RX   I2C_0_SCL   SPI_1_CSn   GP13  17|     |24   GP18   SPI_0_SCK  I2C_1_SDA
                                    GND   18|     |23   GND
            I2C_1_SDA   SPI_1_SCK   GP14  19|     |22   GP17   SPI_0_CSn  I2C_0_SCL   UART_0_RX
            I2C_1_SCL   SPI_0_TX    GP15  20|     |21   GP16   SPI_0_RX   I2C_0_SDA   UART_0_TX
*/

#define BAUD_RATE 115200

#define PIN_IMU_SDA 16
#define PIN_IMU_SCL 17

#define PIN_GNSS_SDA 12
#define PIN_GNSS_SCL 13

#define PIN_SD_MISO 0
#define PIN_SD_CS 1
#define PIN_SD_SCK 2
#define PIN_SD_MOSI 3


