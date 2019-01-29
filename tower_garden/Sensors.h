// Sensor header file
#ifndef Sensors_h
#define Sensors_h

#if (ARDUINO < 100)
#include "WProgram.h"
#else
#include <Arduino.h>
#endif


// Sensor heartbeat = Interval for sensor reporting status
#define SENSOR_HEART_BEAT 12000 // 20 minutes in seconds
#define	SENSOR_SCAN_PERIOD 1000		// scan frequency for sensor control.
#define SCAN_DEBOUNCE_TIME 20 // ammount of time to wait before next scan interval. Work around for scan calc.
#define WATER_PUMP_INTERVAL 900 // 15 minutes in seconds
#define LIGHT_TOWER_INTERVAL 43200 // 12 hours in seconds
// IO MAPPING
#define LIGHT_TOWER_PIN 4 // Digital IO for Light tower
#define WATER_PUMP_PIN 5 // Digital IO for Water Pump
#define DOW_1_PIN 6 // Dallas 1 wire sensor 1
#define DOW_2_PIN 7 // Dallas 1 wire sensor 1

typedef enum {
	// INDEX of system message types
	// used to switch between message types
	// See incoming message switch
	get_sysStatus 	= 10, // returns system status msg
	set_sysPause 		= 15, // Pause system (Turn off and wait)
	set_lightTower 	= 20, // set state of light tower
	set_waterPump 	= 25, // set state of water pump
	post_sysStatus 	= 30, // post system state


} MsgTypeIDIndex; 



typedef enum {
// Listing of sensor commands

} CommandIndex;

typedef struct {
	unsigned int startup_count;
} _startup_counter;
_startup_counter startup_counter;

typedef struct {
	byte 	m1; 				// metadata value 1 (byte 10)
	byte  progNum; 		// program number, reference to pattern list (byte 10)
	byte 	m2; 				// metadata value 2 (byte 10)
	int 	runSeconds;	// number of seconds to run each pattern
} _Sensor_progCtrl;
_Sensor_progCtrl Sensor_progCtrl;


typedef struct {
	byte 	m1;
	byte 	sysState;
} _Sensor_sysCtrl;
_Sensor_sysCtrl Sensor_sysCtrl;




// Internal structure to record system state
typedef struct {
	byte m1 = 10;
	byte lightTower_state = 1;
	byte m2 = 10;
	byte waterPump_state = 1;
	byte m3 = 42;
	float temp_sensor_1;
	byte m4 = 42;
	float humidity_sensor_1;
	byte m5 = 42;
	float temp_sensor_2;
	byte m6 = 42;
	float humidity_sensor_2;


} _sysState;
_sysState sysState;




#endif

















