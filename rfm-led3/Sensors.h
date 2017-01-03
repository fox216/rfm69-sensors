// Sensor header file
#ifndef Sensors_h
#define Sensors_h

#if (ARDUINO < 100)
#include "WProgram.h"
#else
#include <Arduino.h>
#endif

#define LED1 18 // A4
#define SENSOR_HEART_BEAT 7500 // 5 seconds
#define SENSOR_BYTES_FREQ 2000 // 2 seconds
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

// typedef struct {
//   byte      m1;
//   byte      led1;
//   byte      m2;
//   byte      led2;
// } _Sensor_t5;
// _Sensor_t5 Sensor_t5;

// typedef struct {
//   byte              m1;
//   unsigned long     runCount;
//   byte              m2;
//   unsigned long     MillSecs;
// } _Sensor_t100;
// _Sensor_t100 Sensor_t100;

// typedef struct {
//   byte      m1;
//   long      humdity;
// } _Sensor_101;
// _Sensor_101 Sensor_101;


typedef struct {
  byte      m1;
  unsigned int      led1_mode;
} _Sensor_15;
_Sensor_15 Sensor_15;

typedef struct {
  byte              m1;
  unsigned long     runCount;
  byte              m2;
  unsigned long     MillSecs;
} _Sensor_100;
_Sensor_100 Sensor_100;


#endif