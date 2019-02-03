// Tower Garden Sensor

#include <NodeMsg.h>
#include <NodeConf.h>
#include <Sensors.h>
// Sensor capabilities
#include <RFM69.h>
#include <SPI.h>
#include <OneWire.h>
#include <DS2438.h>

RFM69 radio;
bool 	readyToXmit = false;
int 	msgSize = 0;

/* JeeNode Relay Pinout
	P = 5V
	D = Digital Input (Relay D)
	G = Ground
	A = Digital Input (Relay A)

	Wire Color Code

*/

/* Dallas One Wire Pinout
	Blue/White = Ground
	Blue = Signal
	Orange = 5V 
	2k resistor between 5v and signal
*/

const uint8_t OWP_1 = DOW_1_PIN;
const uint8_t OWP_2 = DOW_2_PIN;

/* Dallas one wire Pin 5
-Smart Battery Monitor (2438)
Address=26 C B7 6B 0 0 0 6
-Programmable Thermometer (18B20)
Address=28 61 37 C9 0 0 0 95
-256 EEPROM (2430A)
Address=14 B8 CC 69 2 0 0 E6
*/
uint8_t DS2438_1_addr[] = { 0x26, 0x0C, 0xB7, 0x6B, 0x00, 0x00, 0x00, 0x06 };


/* Dallas one wire Pin 6
-Smart Battery Monitor (2438)
Address=26 33 B2 6B 0 0 0 1D 
-Programmable Thermometer (18B20)
Address=28 18 65 C9 0 0 0 8D
-256 EEPROM (2430A)
Address=14 D D4 69 2 0 0 48
*/
uint8_t DS2438_2_addr[] = { 0x26, 0x33, 0xB2, 0x6B, 0x00, 0x00, 0x00, 0x1D };

OneWire ows1(OWP_1);
DS2438 ds2438_1(&ows1, DS2438_1_addr);

OneWire ows2(OWP_2);
DS2438 ds2438_2(&ows2, DS2438_2_addr);

void collect_dow_data() {
	ds2438_1.update();
	sysState.temp_sensor_1 = ((ds2438_1.getTemperature() * C2F) + 32) - TEMP_CAL;
	sysState.humidity_sensor_1 = ds2438_1.getVoltage(DS2438_CHA);
	ds2438_2.update();
	sysState.temp_sensor_2 = ((ds2438_2.getTemperature() * C2F) +32)  - TEMP_CAL;
	sysState.humidity_sensor_2 = ds2438_2.getVoltage(DS2438_CHA);
}

void Blink() {
  digitalWrite(PIN,HIGH);
  delay(PIN_DELAY);
  digitalWrite(PIN,LOW);
}

void send_sysState() {
	//** collect current state from sensors
	collect_dow_data();
	// send message to gateway
	nodeMsg.NodeID = 1;
	nodeMsg.Method = 4;
	// Message Type = get_sysState
	nodeMsg.TypeID = 10;

	memcpy(nodeMsg.MsgPayload, &sysState, sizeof(_sysState));
	msgSize = MSG_HEADER_SZ + sizeof(_sysState);
	radio.send(nodeMsg.NodeID, (const void*)(&nodeMsg), msgSize);
	/*
	{"node":64,"meth":4,"type":10,"rssi":-65,"datasz":32,"data":[41,0,0,10]}
	*/
	Blink();
}

void light_ctrl() {
	// toggle light tower state
	if (sysState.lightTower_state == ON) {
		sysState.lightTower_state = OFF;
	} else {
		sysState.lightTower_state = ON;
	}
	// sysState.lightTower_state = ! sysState.lightTower_state;
	if (sysState.lightTower_state == ON) {
		// Turn on light tower
		digitalWrite(LIGHT_TOWER_PIN, HIGH);
	} else {
		// Turn off light tower
		digitalWrite(LIGHT_TOWER_PIN, LOW);
	}
	send_sysState();
}

void water_ctrl() {
	// toggle water pump state
	if (sysState.waterPump_state == ON) {
		sysState.waterPump_state = OFF;
	} else {
		sysState.waterPump_state = ON;
	}
	// sysState.waterPump_state = ! sysState.waterPump_state;
	if (sysState.waterPump_state == ON) {
		// Turn on water pump
		digitalWrite(WATER_PUMP_PIN, HIGH);
	} else {
		// Turn off water pump
		digitalWrite(WATER_PUMP_PIN, LOW);
	}
	send_sysState();
}

void setup()  {
  delay( 20000 ); // power-up safety delay
  Serial.begin(115200);
  pinMode(LIGHT_TOWER_PIN, OUTPUT);
	pinMode(WATER_PUMP_PIN, OUTPUT);
	pinMode(PIN, OUTPUT);
	// Start dallas one wire
	ds2438_1.begin();
	ds2438_2.begin();


  // Initialize Radio 
  radio.initialize(FREQUENCY, NODEID, NETWORKID);
  radio.encrypt(KEY);
  // enable system
  water_ctrl();
  light_ctrl();
}// END SETUP

void loop() {
  // Process incoming message / action
  if (radio.receiveDone() ) {
    // Convert radiio data to sensor message
    nodeMsg = *(_NodeMsg*)radio.DATA;
    switch(nodeMsg.TypeID) {
      case get_sysStatus:
      	send_sysState();
      break;
      case set_sysPause:
      break;
      case set_lightTower:
      break;
      case set_waterPump:
      break;
    }
  } // END MSG Processing
  // raw counter
  if (millis() % SENSOR_SCAN_PERIOD == 0) {
  	sysState.run_count += 1;
	  if (sysState.run_count % WATER_PUMP_INTERVAL == 0) {
	  	water_ctrl();
	  }
	  if (sysState.run_count % LIGHT_TOWER_INTERVAL == 0 ) {
	  	light_ctrl();
	  }
	  delay(20);
	}
}