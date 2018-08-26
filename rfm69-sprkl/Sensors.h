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
#define SPRKL_DWELL_TIME 5000 // Delay seconds between switching zones
#define	SENSOR_SCAN_PERIOD 1000		// scan frequency for sensor control.
#define SCAN_DEBOUNCE_TIME 20 // ammount of time to wait before next scan interval. Work around for scan calc.

typedef struct {
  // Metadata (Byte: 10 )
  byte			m1;
  byte			zoneNum;
  // Metadata (Integer: 20 )
  byte      m2;
  int       runSeconds;
} _Sensor_zoneCtrl;
_Sensor_zoneCtrl Sensor_zoneCtrl;

typedef struct {
	byte 	m1; 				// metadata value 1 (byte 10)
	byte  progNum; 		// program number, reference to zone list (byte 10)
	byte 	m2; 				// metadata value 2 (byte 10)
	int 	runSeconds;	// number of seconds to run each zone
} _Sensor_progCtrl;
_Sensor_progCtrl Sensor_progCtrl;


typedef struct {
	byte 	m1;
	byte 	sysState;
} _Sensor_sysCtrl;
_Sensor_sysCtrl Sensor_sysCtrl;

// map of zones to IO ports
typedef enum {
	zone1 = 8, 	// Solid State Relay  1
	zone2 = 7, 		// Solid State Relay  2
	zone3 = 6, 		// Solid State Relay  3
	zone4 = 5, 		// Solid State Relay  4
	zone5 = 15, 		// Solid State Relay  5
	zone6 = 16, 		// Solid State Relay  6
	zone7 = 17, 	// Solid State Relay  7
	zone8 = 3, 	// Solid State Relay  7
	zone9 = 4, 	// Solid State Relay  9
	zone10 = 14, 	// Solid State Relay  9
} ZoneIoMap;

byte zoneList[] = {
	zone1, 
	zone2, 
	zone3, 
	zone4, 
	zone5, 
	zone6, 
	zone7, 
	zone8, 
	zone9,
	zone10,
};

byte frontList[] = {
	zone1,
	zone2,
	zone3,
	zone4,
//	zone10,
};

byte backList[] = {
	zone5,
	zone6,
	zone7,
	zone8,
};

byte allList[] = {
	zone1,
	zone2,
	zone3,
	zone4,
	zone5,
	zone6,
	zone7,
	zone8,
	//zone10,
};

typedef enum {
	// INDEX of system message types
	// used to switch between message types
	// See incoming message switch
	heartbeat		= 10,
	zoneCtrl 		= 20,    	// Control individual Zone
	progCtrl 		= 30, 		// Control predefined groups of Zones
	sysCtrl 		= 40,		// System contol message (Override functions)
	sysStatus		= 50,		// System status callback
} MsgTypeIndex; 


// Internal structure to record system state
typedef struct {
	bool	sysActive;		// T/F system active
	bool 	zoneActive;		// T/F zone status. Added for pause
	bool 	runProgram;		// T/F set if program configured to run
	byte  runMode;			// Equal to sensor type aka TypeID
	byte  *progPtr;			// pointer to the program array 
	byte 	progArrSize;	// size of the array the pointer is pointing 
//	char 	sysCurState;	// System State: (R: Run, P: Paused, I: Idle, C: Cancel) 
//	char 	progName;		// Store requested program
//	byte 	currentZone;	// Current Zone Active
	byte 	zoneAcc;		// Zone accumulator (Index of zone set)
//	char 	systemState;	// Store system state
	int		cycleCount;		// number of cycles run 
	int		cycleLimit;		// max number of cycles to run
} _SysState;
_SysState sysState;




#endif

















