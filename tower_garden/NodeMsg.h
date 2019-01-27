/*
	This file contains common message types for all 
	sensors and gateway nodes used in the RFM69 implementation
	Usage
	Link to project workspace
*/

#ifndef NodeMsg_h
#define NodeMsg_h

#if (ARDUINO < 100)
#include "WProgram.h"
#else
#include <Arduino.h>
#endif
 
#define MAX_NETWORK_SIZE 60
#define MAX_PAYLOAD_SIZE 40

// Arduino Data Sizes
//----------------------------
// Datatype			RAM usage
// boolean			1 byte
// char				1 byte
// unsigned char	1 byte
// int				2 byte
// unsigned int		2 byte
// word				2 byte
// long				4 byte
// unsigned long	4 byte
// float			4 byte
// double			4 byte

// Message Rules
// 1. Data exchanged between gateway and host machine must be expressed as a serialized array of objects
// 2. Data format is sensor specific. Allows for maximum flexiblity for sensor programming.
// 3. Systems connected to the gateway are associated with database containing sensor message structures 
// 4. Payload message types difined in msgDataTypes

// Update for marshalling data in array. Encoding types as bytes
// Serialized exmaple removing map declaration
// echo '{"node":"14","meth":2,"type":6,"data":[10,2,41,250445,42,321.45,42,88.45]}' > /dev/ttyLPL 
// echo '{"node":"44","meth":2,"type":6,"data":[10,42,41,250454745,42,321.45,42,88.45,20,53]}' > /dev/ttyGW2

#define MSG_HEADER_SZ 3 // used to calc transmission size.
typedef struct { 
  byte 				NodeID; 		// Address of target sensor 
  byte 				Method; 		// Message method (Example: Get, Set, Post, etc)
  byte				TypeID; 		// Sensor or system data type
  //byte 				PayloadSize;		// Length message payload (Calculated Field)
  //const char*		PayloadDataMap;		// Character Map used to decode MsgPayload data 
  byte  			MsgPayload[MAX_PAYLOAD_SIZE]; // ordered set of data types organized in array
} _NodeMsg;
_NodeMsg nodeMsg;	// serial Message

typedef enum {
	_byte_ 		= 10,		
	_char_ 		= 11,		
	_uchar_ 	= 12,		
	_int_ 		= 20,		
	_uint_ 		= 21,		
	_word_ 		= 22,		
	_long_ 		= 40,		
	_ulong_ 	= 41,		
	_float_ 	= 42,		
	_double_ 	= 43,		
} msgDataTypes;


typedef enum {
	ping 		= 1,
	get 		= 2,
	set 		= 3,
	post 		= 4,
	req			= 5,
	resp 		= 6,
} msgMethodTypes;
#endif

