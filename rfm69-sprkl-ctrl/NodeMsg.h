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
	byte 			MsgID;	// Coordination ID to ack/nak (unknown if needed for applications)
  	byte 			MsgType; // Message type - Struct Decode (10)
  	byte 			msg[16];
} Payload;
Payload payload;


typedef struct {
	byte	zone;			// Zone to activate
	byte	cycleSelect;	// length of time zone should run (Predefined times)
} _zoneCtrl;
_zoneCtrl i_zoneCtrl; // iunbound message type

/*
typedef struct { 
// MESSAGE = 10
	//struct __DefaultMsgHeader dmh;
	byte 			zone; 	// Sprinkler Zone to control
	byte			;		// Duration of sprinkle time
} _SprklMsg;
_SprklMsg	i__SprklMsg;
_SprklMsg 	o__SprklMsg;
*/

#endif

