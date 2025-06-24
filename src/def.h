#ifndef _DEF_H
#define _DEF_H


//--------------------------------------------------------------------------------
// Define GPS module UART pin
//--------------------------------------------------------------------------------

#define GPS_RX 16   // GPS TX -> ESP32 RX(GPIO16)
#define GPS_TX 17   // GPS RX -> ESP32 TX(GPIO17)


//--------------------------------------------------------------------------------
// Define IMU module I2C pin
//--------------------------------------------------------------------------------

#define IMU_SDA 8    // Benware 보드의 GPIO 8번 핀
#define IMU_SCL 9    // Benware 보드의 GPIO 9번 핀


//--------------------------------------------------------------------------------
// Data struct
//--------------------------------------------------------------------------------

typedef struct
{
  bool init;
  bool valid;
  float speed;

} GPSData;


typedef struct
{
  bool valid;
  float accX, accY, accZ; // 가속도 원시 데이터
  float gyroX, gyroY, gyroZ; // 자이로 원시 데이터
  float angleX, angleY, angleZ; // 계산된 각도 (상보 필터 적용)

} IMUData;



#endif

