/*********** SPRINKLER SENSOR MESSAGE STRUCTURE *******************
*/

#ifndef NodeMsg_h
#define NodeMsg_h

#if (ARDUINO < 100)
#include "WProgram.h"
#else
#include <Arduino.h>
#endif
#define FRAME_BUFFER_SIZE 5
#define MAX_SERIAL_SIZE 70 
#define MAX_NETWORK_SIZE 61
#define PAYLOAD_HEADER_SIZE 1

/*---------------------------------------------
|	!! PKG Types !!
|	Structure written to pkg[] array...
|
*/





typedef enum {
	zoneCtrl 		= 10,    	// Control individual Zone
	zoneGroupCtrl 	= 20, 		// Control predefined groups of Zones
	sysCtrl 		= 30,		// System contol message (Override functions)
	sysStatus		= 40,		// System status callback
} MsgTypeIndex;

typedef struct {
  	byte 			MsgType; 	// Message type 
  	byte 			msg[16]; 	// Message Payload
} Payload;
Payload payload;

/*
	Features
	------------------------------------------------
	zoneCtrl: 	Control single zone. Turn on single zone for default run time. 
	runProg:	Run predefined sprinkle program based on control character (Example: Front[f], Back[b])
	sysCtrl:	Pause / Resume system.
	- Not Implemented sysStatus:	Query System status.
	sysConfig:	Set system configuration vales [EPROM]. (Zone run time, Dwell time[Pause time between zones])
*/


typedef struct {
	// _zoneCtrl
	// MESSAGE TYPE = 10
	// MSG_SIZE = 2
	byte	zone;				// Zone to activate
	byte	cycleSelect;		// length of time zone should run (Predefined times)
} _zoneCtrl;
_zoneCtrl i_zoneCtrl; 			// inbound message
_zoneCtrl o_zoneCtrl; 			// outbound message


typedef struct { 
	// _SprklMsg
	// MESSAGE TYPE = 
	// MSG_SIZE = 2 
	byte 		zone; 			// Sprinkler Zone to control
	byte		state;			// Duration of sprinkle time
} _SprklMsg;
_SprklMsg	i_SprklMsg;
_SprklMsg 	o_SprklMsg;

tyepdef struct {
	// _SysStatus
	// MESSAGE Type = 40
	// MSG_SIZE = 
	byte 	zone;  				// Current Zone
	char 	state;				// System State: (R: Run, P: Paused, I: Idle, C: Cancel) 
	byte	runTime;			// Zone run time
	byte	dwellTime;			// Wait time between Zone Switch
	byte	percComplete;		// Percent complete (Range: 0 - 100) 
} _SysCtrl;
_SysStatus	i_SysStatus;
_SysStatus	o_SysStatus;

tyepdef struct {
	char 	program;			// Predefined set of zones in sequence
} _runProg;
_runProg	i_runProg;

#endif

