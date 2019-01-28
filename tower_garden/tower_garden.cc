// Tower Garden Sensor

#include <NodeMsg.h>
#include <NodeConf.h>
#include <Sensors.h>
// Sensor capabilities
#include <RFM69.h>
#include <SPI.h>
#include <OneWire.h>

RFM69 radio;
bool 	readyToXmit = false;
int 	msgSize = 0;

void setup()  {
  delay( 3000 ); // power-up safety delay
  Serial.begin(115200);

  // Initialize Radio 
  radio.initialize(FREQUENCY, NODEID, NETWORKID);
  radio.encrypt(KEY);


}// END SETUP




void loop() {
  // Process incoming message / action
  if (radio.receiveDone() ) {
    // Convert radiio data to sensor message
    nodeMsg = *(_NodeMsg*)radio.DATA;
    switch(nodeMsg.TypeID) {
      case get_sysStatus:
      break;
      case set_sysPause:
      break;
      case set_lightTower:
      break;
      case get_waterPump:
      break;
    }
  } // END MSG Processing
  // raw counter
  if (millis() % WATER_PUMP_INTERVAL == 0) {
  	// toggle water pump state
  	sysState.waterPump_state = ! sysState.waterPump_state;
  	if (sysState.waterPump_state) {
  		digitalWrite(WATER_PUMP_PIN, HIGH);
  	} else {
  		digitalWrite(WATER_PUMP_PIN, LOW);
  	}

  }
  if (millis() % LIGHT_TOWER_INTERVAL == 0 ) {
  	// toggle light tower state
  	sysState.lightTower_state = ! sysState.lightTower_state;
  	if (sysState.lightTower_state) {
  		digitalWrite(LIGHT_TOWER_PIN, HIGH);
  	} else {
  		digitalWrite(LIGHT_TOWER_PIN, LOW);
  	}
  }

}