// Sensor header file
#ifndef Sensors_h
#define Sensors_h

#if (ARDUINO < 100)
#include "WProgram.h"
#else
#include <Arduino.h>
#endif

#define SENSOR_HEART_BEAT 7500 // 5 seconds
#define SENSOR_BYTES_FREQ 2000 // 2 seconds
typedef struct {
  // Metadata (Byte: 10 )
  byte			m1;
  byte			zoneNum;
  // Metadata (Integer: 20 )
  byte      m2;
  int       runSeconds;
} _Sensor_sprkl;
_Sensor_sprkl Sensor_sprkl;

typedef struct {


} _Sensor_Sprkl_State;
_Sensor_Sprkl_State Sensor_Sprkl_State;