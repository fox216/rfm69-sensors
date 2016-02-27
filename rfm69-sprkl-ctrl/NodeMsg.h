/********2*** SPRINKLER SENSOR MESSAGE STRUCTURE *******************
*/

#ifndef NodeMsg_h
#define NodeMsg_h

#if (ARDUINO < 100)
#include "WProgram.h"
#else
#include <Arduino.h>
#endif

// Message Constants
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
	// INDEX of system message types
	// used to switch between message types
	zoneCtrl 		= 10,    	// Control individual Zone
	runProg 		= 20, 		// Control predefined groups of Zones
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
	zoneCtrl: 	[I/O]Control single zone. Turn on single zone for default run time. 
	runProg:	[I/O]Run predefined sprinkle program based on control character (Example: Front[f], Back[b])
	sysCtrl:	[I/O]Pause / Resume system.
	sysStatus:	[O] Send systems state Query System status.
	sysConfig:	[I]Set system configuration vales . (Zone run time, Dwell time[Pause time between zones]) 
				Returns sysStatus message.

*/
typedef enum {
	min2 = 2,		// 2  Minutes
	min5 = 5,		// 5  Minutes
	min10 = 10,		// 10 Minutes
} enCycleSelect;

typedef struct {
	// Name: zoneCtrl
	// MESSAGE TYPE = 10
	// MSG_SIZE = 2
	byte	zone;				// Zone to activate
	byte	cycleSelect;		// length of time zone should run (Predefined times)
} _zoneCtrl;
_zoneCtrl i_zoneCtrl; 			// inbound message
_zoneCtrl o_zoneCtrl; 			// outbound message

tyepdef struct {
	// Name: runProg
	// MESSAGE TYPE = 20
	// MSG_SIZE = 1
	// Program Table
	// A: [A]ll zones in ZoneList
	// F: [F]ront zones in f_zones
	// B: [B]ack zones in b_zones
	char 	program;			// Predefined set of zones in sequence
} _runProg;
_runProg	i_runProg;

typedef struct { 
	// Name: SprklMsg
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
	// MSG_SIZE = 1
	char 	state;				// System State: (R: Run, P: Paused, I: Idle, C: Cancel) 
} _SysCtrl;
_SysCtrl	i_SysCtrl;


tyepdef struct {
	// _SysStatus
	// MESSAGE Type = 40
	// MSG_SIZE = 
	byte 	zone;  				// Current Zone
	char 	state;				// System State: (R: Run, P: Paused, I: Idle, C: Cancel) 
	char    progName;			// Current program
	//byte	runTime;			// ??? Zone run time
	byte	percComplete;		// Percent complete (Range: 0 - 100) 
} _SysStatus;
_SysStatus;	o_SysStatus;





#endif

