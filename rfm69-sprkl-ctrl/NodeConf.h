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

#define NODEID      75
#define GATEWAY     1
#define NETWORKID   50
#define FREQUENCY   RF69_915MHZ //Match this with the version of your Moteino! (others: RF69_433MHZ, RF69_868MHZ)
#define KEY         "thisIsEncryptKey" //has to be same 16 characters/bytes on all nodes, not more not less!
#define LED         9
#define SERIAL_BAUD 115200
#define ACK_TIME    30  // # of ms to wait for an ack
#define WAIT_TIME   1000
#define TRANSMITPERIOD 600000 // 10 min
#define GET_SPKL_STATUS 35000 
#define SENSOR_REPORT_PERIOD 30000 // 30 Seconds
#define SENSOR_HEARTBEAT 310000 // 310 Seconds (5Min 10 Seconds)
#define	SENSOR_SCAN_PERIOD 1000


/*
Application Specific Structures
*/

typedef struct {
	bool	sysActive;		// T/F system active 
	byte 	currentZone;	// Current Zone Active
	int		cycleCount;		// number of cycles run 
	int		cycleLimit;		// max number of cycles to run
} _SysState;
_SysState sysState;

typedef enum {
	min2 = 2,		// 2  Minutes
	min5 = 5,		// 5  Minutes
	min10 = 10,		// 10 Minutes
} enCycleSelect;

typedef enum {
	zone1 = 15, 	// Relay 0
	zone2 = 16, 	// Relay 1
	zone3 = 18, 	// Relay 2
	zone4 = 3, 		// Relay 3
	zone5 = 5, 		// Relay 4
	zone6 = 14, 	// Relay 5
	zone7 = 17, 	// Relay 6
	zone8 = 19, 	// Relay 7
	zone9 = 4, 		// Relay 8
	zone10 = 6 	  	// Relay 9
} ZoneIoMap;
// List of all zones
int zoneList[] = {
	zone1, zone2, zone3, zone4, zone5, 
	zone6, zone7, zone8, zone9, zone10
};


#endif

