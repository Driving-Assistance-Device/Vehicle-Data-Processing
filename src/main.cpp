//================================================================================
//
// 
//  
//================================================================================

#include <Arduino.h>
#include "def.h"
#include "GPS.h"
#include "IMU.h"


//--------------------------------------------------------------------------------
// Serial print
//--------------------------------------------------------------------------------

void serial_run()
{
    Serial.print("Speed : ");
    Serial.print( gpsData.speed, 0 );
    Serial.println(" km/h");


    // IMU 데이터가 유효할 때 각도 출력
    // if (imuData.valid)
    // {
    //   Serial.print("  |  Angle_X: ");
    //   Serial.print(imuData.angleX, 1);
    //   Serial.print(" deg");
    //   Serial.print("  |  Angle_Y: ");
    //   Serial.print(imuData.angleY, 1);
    //   Serial.print(" deg");
    // }
    // Serial.println();
}


//--------------------------------------------------------------------------------
//
//--------------------------------------------------------------------------------

void setup()
{
  Serial.begin(115200);

  GPS_init();
  // IMU_init();
}


void loop()
{
  GPS_run();
  // IMU_run();

  serial_run();


}

