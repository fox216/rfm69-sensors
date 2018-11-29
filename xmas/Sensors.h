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
  byte			brightnessNum;
} _Sensor_brightnessCtrl;
_Sensor_brightnessCtrl Sensor_brightnessCtrl;

typedef struct {
  // Metadata (Byte: 10 )
  byte			m1;
  byte			speedNum;
} _Sensor_speedCtrl;
_Sensor_speedCtrl Sensor_speedCtrl;


typedef enum {
	// INDEX of system message types
	// used to switch between message types
	// See incoming message switch
	heartbeat					= 10,
	patternCtrl 			= 20,    	// Control pattern
	brightnessCtrl 		= 30, 		// Control predefined groups of Zones
	speedCtrl 				= 40,		// System contol message (Override functions)
	sysStatus					= 50,		// System status callback
} MsgTypeIndex; 


typedef enum {
	defaultPattern		= 10, 	// default LED pattern
	candyCane					= 11,		// candy cane pattern
	fire							= 12,		// fire pattern
	midnightBlue			= 13,		// Midnight blue pattern
	rainbows					= 14,		// rainbow pattern
	fireBurst					= 15, 	// Fire burst pattern
	Xmas							= 16,
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
	bool	sysActive;		// T/F system active
	bool 	patternActive;		// T/F pattern status. Added for pause
	bool 	runProgram;		// T/F set if program configured to run
	byte  runMode;			// Equal to sensor type aka TypeID
	byte  *progPtr;			// pointer to the program array 
	byte 	progArrSize;	// size of the array the pointer is pointing 
//	char 	sysCurState;	// System State: (R: Run, P: Paused, I: Idle, C: Cancel) 
//	char 	progName;		// Store requested program
//	byte 	currentpattern;	// Current pattern Active
	byte 	patternAcc;		// pattern accumulator (Index of pattern set)
//	char 	systemState;	// Store system state
	int		cycleCount;		// number of cycles run 
	int		cycleLimit;		// max number of cycles to run
} _SysState;
_SysState sysState;




#endif

















