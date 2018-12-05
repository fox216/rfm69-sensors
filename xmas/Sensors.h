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
#define	SENSOR_SCAN_PERIOD 1000		// scan frequency for sensor control.
#define SCAN_DEBOUNCE_TIME 20 // ammount of time to wait before next scan interval. Work around for scan calc.

typedef struct {
  // Metadata (Byte: 10 )
  byte			m1;
  byte			patternNum;
} _Sensor_patternCtrl;
_Sensor_patternCtrl Sensor_patternCtrl;


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
  byte			m1;
  byte			chanceOfGlitter;
} _Sensor_glitterCtrl;
_Sensor_glitterCtrl Sensor_glitterCtrl;



typedef enum {
	// INDEX of system message types
	// used to switch between message types
	// See incoming message switch
	heartbeat					= 10,
	patternCtrl 			= 20,    	// Control pattern
	brightnessCtrl 		= 30, 		// Control predefined groups of Zones
	speedCtrl 				= 40,		// System contol message (Override functions)
	glitterCtrl 			= 42,		// System contol message (Override functions)
	sysStatus					= 250,		// System status callback
	resetDefaults			= 251,
} MsgTypeIndex; 


typedef enum {
	defaultPattern		= 10, 	// default LED pattern
	candyCane					= 11,		// candy cane pattern
	fire							= 12,		// fire pattern
	midnightBlue			= 13,		// Midnight blue pattern
	rainbows					= 14,		// rainbow pattern
	fireBurst					= 15, 	// Fire burst pattern
	Xmas							= 16,
	Merica						= 17,
	glitter_on				= 200,	// add glitter to pattern
	glitter_off				= 201,	// add glitter to pattern
	garlandOff				= 250,	// Turn off Garland

} PatternIndex;


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

// map of patterns to IO ports
typedef enum {
	pattern1 = 8, 	// Solid State Relay  1
	pattern2 = 7, 		// Solid State Relay  2
	pattern3 = 6, 		// Solid State Relay  3
	pattern4 = 5, 		// Solid State Relay  4
	pattern5 = 15, 		// Solid State Relay  5
	pattern6 = 16, 		// Solid State Relay  6
	pattern7 = 17, 	// Solid State Relay  7
	pattern8 = 3, 	// Solid State Relay  7
	pattern9 = 4, 	// Solid State Relay  9
	pattern10 = 14, 	// Solid State Relay  9
} patternIoMap;

// Internal structure to record system state
typedef struct {
	bool	ledsOn;
	bool	glitter;
	byte 	chanceOfGlitter;
	byte  updatesPerSecond;
	byte 	ledsBrightness;
} _SysState;
_SysState sysState;




#endif

















