// Sensor header file
//
// rfm-led2
//
#ifndef Sensors_h
#define Sensors_h

#if (ARDUINO < 100)
#include "WProgram.h"
#else
#include <Arduino.h>
#endif


#define LED1 3
#define LED2 16
#define SENSOR_HEART_BEAT 5050 // 5 seconds
#define HUMIDITY_SENSOR 3 // analog pin 3 A3
#define HUMIDITY_READ_FREQ 10000 // 30 Seconds
typedef struct {
  byte			m1;
  byte			b1;
  byte			m2;
  unsigned long	L1;
  byte			m3;
  float			f1;
  byte			m4;
  float			f2;
  byte			m5;
  int			i1;
} _Sensor_t6;
_Sensor_t6 Sensor_t6;

typedef struct {
  byte      m1;
  byte      led1;
  byte      m2;
  byte      led2;
} _Sensor_t5;
_Sensor_t5 Sensor_t5;

typedef struct {
  byte              m1;
  unsigned long     runCount;
  byte              m2;
  unsigned long     MillSecs;
} _Sensor_t100;
_Sensor_t100 Sensor_t100;

typedef struct {
  byte      m1;
  long      humdity;
} _Sensor_101;
_Sensor_101 Sensor_101;



#endif