// Sensor header file
#ifndef Sensors_h
#define Sensors_h

#if (ARDUINO < 100)
#include "WProgram.h"
#else
#include <Arduino.h>
#endif


// Sensor heartbeat = Interval for sensor reporting status
#define SENSOR_HEART_BEAT 12000 // 20 minutes in seconds
#define	SENSOR_SCAN_PERIOD 1000		// scan frequency for sensor control.
#define SCAN_DEBOUNCE_TIME 20 // ammount of time to wait before next scan interval. Work around for scan calc.
#define WATER_PUMP_INTERVAL 900 // 15 minutes in seconds
#define LIGHT_TOWER_DURATION 43200 // 12 hours in seconds

// EEPROM BYTES 1024



// Structure to set the brightness (intensity of the LEDs)
typedef struct {
  // Metadata (Byte: 10 )
  byte			m1;
  float			brightnessNum;
} _Sensor_brightnessCtrl;
_Sensor_brightnessCtrl Sensor_brightnessCtrl;

typedef struct {
  // Metadata (Byte: 10 )
  byte			m1;
  float			speedNum;
} _Sensor_speedCtrl;
_Sensor_speedCtrl Sensor_speedCtrl;

typedef struct {
  // Metadata (Byte: 10 )
} _Sensor_glitterCtrl;
_Sensor_glitterCtrl Sensor_glitterCtrl;



typedef enum {
	// INDEX of system message types
	// used to switch between message types
	// See incoming message switch

} MsgTypeIndex; 


typedef enum {
// Listing of EEProm memory offset locations

} EEPROM_Address_Offset;

typedef enum {
// Listing of sensor commands

} CommandIndex;


typedef struct {
	byte 	m1; 				// metadata value 1 (byte 10)
	byte  progNum; 		// program number, reference to pattern list (byte 10)
	byte 	m2; 				// metadata value 2 (byte 10)
	int 	runSeconds;	// number of seconds to run each pattern
} _Sensor_progCtrl;
_Sensor_progCtrl Sensor_progCtrl;


typedef struct {
	byte 	m1;
	byte 	sysState;
} _Sensor_sysCtrl;
_Sensor_sysCtrl Sensor_sysCtrl;


// Internal structure to record system state
typedef struct {

} _SysState;
_SysState sysState;




#endif

















