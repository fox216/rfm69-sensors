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
	
	
} MsgTypeIndex;

typedef struct {
	byte 			MsgID;	// Coordination ID to ack/nak (unknown if needed for applications)
  	byte 			MsgType; // Message type - Struct Decode (10)
  	byte 			msg[16];
} Payload;
Payload payload;


typedef struct { 
// MESSAGE = 10
	//struct __DefaultMsgHeader dmh;
	byte 			zone; 	// Sprinkler Zone to control
	byte			;		// Duration of sprinkle time
} _SprklMsg;
_SprklMsg	i__SprklMsg;
_SprklMsg 	o__SprklMsg;


#endif

/*
NOTES 
	Sprinkler IO Map
	PIN 	RELAY
	---		-----
	D3		3
	D4 		8
	D5 		4
	D6 		9
	D7		NC
	D8 		NC
	D14 	5
	D15 	0
	D16		1
	D17 	6
	D18		2
	D19		7

*/