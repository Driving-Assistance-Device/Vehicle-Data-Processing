#ifndef _GPS_h
#define _GPS_h

#include <HardwareSerial.h>
#include <TinyGPS.h>
#include "def.h"


extern TinyGPS gps;
extern HardwareSerial gpsSerial;


extern GPSData gpsData;


extern void GPS_init();
extern void GPS_run();



#endif



