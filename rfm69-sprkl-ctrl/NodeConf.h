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

// Sprinkler Zone IO Map
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
// Enum Zone List
int zoneList[] = {
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


#endif

