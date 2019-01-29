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

uint8_t DS2438_1_addr[] = { 0x26, 0x33, 0xB2, 0x6B, 0x00, 0x00, 0x00, 0x1D };
uint8_t DS2438_2_addr[] = { 0x26, 0x33, 0xB2, 0x6B, 0x00, 0x00, 0x00, 0x1D };

OneWire ows1(DOW_1_PIN);
DS2438 ds2438_1(&ows1, DS2438_1_addr);

OneWire ows2(DOW_2_PIN);
DS2438 ds2438_2(&ows2, DS2438_1_addr);


void setup()  {
  delay( 3000 ); // power-up safety delay
  Serial.begin(115200);

  // Initialize Radio 
  radio.initialize(FREQUENCY, NODEID, NETWORKID);
  radio.encrypt(KEY);


}// END SETUP

void collect_dow_data() {
	sysState.temp_sensor_1 = ds2438_1.getTemperature();
	sysState.humidity_sensor_1 = ds2438_1.getVoltage(DS2438_CHA);
	sysState.temp_sensor_2 = ds2438_2.getTemperature();
	sysState.humidity_sensor_2 = ds2438_2.getVoltage(DS2438_CHA);
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

}



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
  if (millis() % WATER_PUMP_INTERVAL == 0) {
  	// toggle water pump state
  	sysState.waterPump_state = ! sysState.waterPump_state;
  	if (sysState.waterPump_state == 1) {
  		// Turn on water pump
  		digitalWrite(WATER_PUMP_PIN, HIGH);
  	} else {
  		// Turn off water pump
  		digitalWrite(WATER_PUMP_PIN, LOW);
  	}

  }
  if (millis() % LIGHT_TOWER_INTERVAL == 0 ) {
  	// toggle light tower state
  	sysState.lightTower_state = ! sysState.lightTower_state;
  	if (sysState.lightTower_state == 1) {
  		// Turn on light tower
  		digitalWrite(LIGHT_TOWER_PIN, HIGH);
  	} else {
  		// Turn off light tower
  		digitalWrite(LIGHT_TOWER_PIN, LOW);
  	}
  }

}