/*********** GATEWAY MESSAGE STRUCTURE *******************
Gateways structure is a simplified, abstracted, message 
type used to relay messages between host computer and 
wireless sensor network. 

Gateway message format 
HEADER
	- MESSAGE PAYLOAD

Function:
Gateway relays messages by inspecting only the message 
header. Payload forwarded to target node intact...

MOTEINO MESSAGE FORMAT
----------------------------------

MAX_MESSAGE_SIZE = 66
MESSAGE FRAME SIZES
------------------------
PAYLOAD = 1
ADDRESS_BYTE = 1
FROM_ADDRESS = 1
CONTROL_BYTE = 1
NETWORK_ID = 1
MAX_PAYLOAD = 66 - 5 = 61 BYTES!!!
_____________________________________
Moteino References 
https://github.com/LowPowerLab/RFM69
http://lowpowerlab.com/blog/2013/06/20/rfm69-library/#more-917

Developer Notes
1. Payload is not inspected by the gateway. 
2. Header inspected by Gateway, used to route message
3. Target node is responsible for processing payload.
4. ASSUMPTION = AVR(Big Endian) RPI(Little Endian)
5. NodeID + MsgID used together to create unique index for xmit.
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
//#define MAX_PAYLOAD_SIZE 59 // Package size in payload
#define WATCHDOG_DEFAULT 10000 // 10 seconds used by node
#define PAYLOAD_HEADER_SIZE 2
/*---------------------------------------------
|	!! PKG Types !!
|	Structure written to pkg[] array...
|
*/


/*
 - Report Node Message definition. 
 Test message for building our relay thought node-red. 

*/

typedef enum {
	ReportMsg = 10,
	MillsCount = 20,
} MsgTypeIndex;

typedef struct {
	byte 			MsgID;	// Coordination ID to ack/nak (unknown if needed for applications)
  	byte 			MsgType; // Message type - Struct Decode (10)
  	byte 			msg[18];
} Payload;
Payload payload;


typedef struct { 
	// MESSAGE = 10
	// Add collection message data types for node red parsing
	byte				bt;		//[1] Byte			
	int 				si;		//[4] Signed Int
	unsigned int 		ui;		//[4] Unsigned Int
	float 				fp; 	//[4] Float
	double				db; 	//[4] double
	char				sc;		//[1] Single character 
} _ReportMsg;
_ReportMsg i_ReportMsg;
_ReportMsg o_ReportMsg;



typedef struct {
	unsigned int 	mills; 		// Pin number for the Led
} _MillsCount;
_MillsCount o_MillsCount; 	// AKA Heartbeat


#endif