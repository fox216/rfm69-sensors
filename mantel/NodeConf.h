// XMAS
// !!!!  DEVICE CONFIGURATION SETTINGS  !!!!
#ifndef NodeConf_h
#define NodeConf_h

#if (ARDUINO < 100)
#include <WProgram.h>
#else
#include <Arduino.h>
#endif

/*---------------------------------------------
|
|	Node Configuration Settings
|	
*/

// Configuration for RFM69 Radio
#define NODEID      31
#define NETWORKID   60 // 50 for testing... change to production (100)
#define FREQUENCY   RF69_915MHZ //Match this with the version of your Moteino! (others: RF69_433MHZ, RF69_868MHZ)
#define KEY         "thisIsEncryptKey" //has to be same 16 characters/bytes on all nodes, not more not less!
// Configuration for Serial port
#define SERIAL_BAUD 115200

#define LED         9
#define ACK_TIME    30  // # of ms to wait for an ack
// #define WAIT_TIME   1000
// Heartbeat message frequency
#define TRANSMITPERIOD 600000 // 10 min


#endif