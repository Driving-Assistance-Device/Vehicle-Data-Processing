#include "GPS.h"


TinyGPS gps;
HardwareSerial gpsSerial( 1 ); // UART1 (Serial1 GPIO 16, 17)

GPSData gpsData;

//--------------------------------------------------------------------------------

static void gpsData_init()
{
  gpsData.init = false;
  gpsData.valid = false;
  gpsData.speed = 0;
}


void GPS_init()
{
  gpsData_init();

  gpsSerial.begin( 9600, SERIAL_8N1, GPS_RX, GPS_TX );

  Serial.println("------------------------------");
  Serial.println("Init GPS");
  Serial.println("------------------------------");

  gpsData.init = true;
}


void GPS_run()
{
  for ( unsigned long start = millis(); millis() - start < 1000; )
  {
    while ( gpsSerial.available() )
    {
      char c = gpsSerial.read();

      if ( gps.encode( c ) ) {
        gpsData.valid = true;
      }
    }
  }

  if ( gpsData.valid )
  {
    float speed_kmph = gps.f_speed_kmph();

    if ( speed_kmph != TinyGPS::GPS_INVALID_F_SPEED ) {
      gpsData.speed = speed_kmph;
    }
    else {
      gpsData.speed = -1;
    }
  }
}
