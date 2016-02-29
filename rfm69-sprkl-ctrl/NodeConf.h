// !!!!  SPRINKLE - DEVICE CONFIGURATION SETTINGS  !!!!
#ifndef NodeConf_h
#define NodeConf_h

#if (ARDUINO < 100)
#include "WProgram.h"
#else
#include <Arduino.h>
#endif

/*---------------------------------------------
|
|	Node Configuration Settings
|	
*/

#define NODEID      64
#define GATEWAY     1
#define NETWORKID   50
#define FREQUENCY   RF69_915MHZ //Match this with the version of your Moteino! (others: RF69_433MHZ, RF69_868MHZ)
#define KEY         "thisIsEncryptKey" //has to be same 16 characters/bytes on all nodes, not more not less!
#define LED         9
#define SERIAL_BAUD 115200
#define ACK_TIME    30  // # of ms to wait for an ack
#define SPRKL_DWELL_TIME	200		// Set sprinkle dwell time
#define GET_SPKL_STATUS 35000 
#define SENSOR_HEARTBEAT 900250 	// Send sensor haertbeat message (15 Min & 250 ms)
//#define SENSOR_HEARTBEAT 3000 	// Send sensor haertbeat message (3 seconds for DEBUG)
#define	SENSOR_SCAN_PERIOD 1000		// scan frequency for sensor control.
#define DEBUG_ENABLED  1

/*
Application Specific Structures
*/

// Interal struct for program state.
typedef struct {
	bool	sysActive;		// T/F system active
	bool 	zoneActive;		// T/F zone status. Added for pause
	bool 	runProgram;		// T/F set if program configured to run
	char 	sysCurState;	// System State: (R: Run, P: Paused, I: Idle, C: Cancel) 
	char 	progName;		// Store requested program
	byte 	currentZone;	// Current Zone Active
	byte 	zoneAcc;		// Zone accumulator (Index of zone set)
	char 	systemState;	// Store system state
	int		cycleCount;		// number of cycles run 
	int		cycleLimit;		// max number of cycles to run
} _SysState;
_SysState sysState;

typedef enum {
	min2 = 2,		// 2  Minutes
	min5 = 5,		// 5  Minutes
	min10 = 10,		// 10 Minutes
} enCycleSelect;

// Sprinkler Zone IO Map
// Abstraction for zone map
typedef enum {
	zone1 = 17, 	// Solid State Relay  1
	zone2 = 4, 		// Solid State Relay  2
	zone3 = 5, 		// Solid State Relay  3
	zone4 = 6, 		// Solid State Relay  4
	zone5 = 7, 		// Solid State Relay  5
	zone6 = 8, 		// Solid State Relay  6
	zone7 = 14, 	// Solid State Relay  7
	zone8 = 15, 	// Solid State Relay  7
	zone9 = 16, 	// Solid State Relay  9
} ZoneIoMap;

typedef enum {
	z1 = 1,
	z2 = 2,
	z3 = 3,
	z4 = 4,
	z5 = 5,
	z6 = 6,
	z7 = 7,
	z8 = 8,
	z9 = 9
} ZoneReportMap;

byte zoneReportList[] = {
	z1,
	z2,
	z3,
	z4,
	z5,
	z6,
	z7,
	z8,
	z9
};

// Enum Zone List
// TODO: Determine format for zones, consider byte (program memory)
byte zoneList[] = {
	zone1, 
	zone2, 
	zone3, 
	zone4, 
	zone5, 
	zone6, 
	zone7, 
	zone8, 
	zone9
};

// ----	Define programs	----
// Front Zones
byte f_zones[] = {
	zone1, 
	zone2, 
	zone3, 
	zone4, 
};
// Back Zones
byte b_zones[] = {
	zone5, 
	zone6, 
	zone7, 
	zone8,
	zone9 
};





#endif

