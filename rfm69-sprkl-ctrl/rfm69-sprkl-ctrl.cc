/*
Sprinkler Sensor 
Controls in-ground sprinkler system
*/
#include <RFM69.h>
#include <SPI.h>
#include <NodeMsg.h> // Load Gateway Message structure
#include <NodeConf.h>
// declare radio
RFM69 radio;
bool wd_active = false;
bool promiscuousMode = false; //set to 'true' to sniff all packets on the same network

void disableAllZones(){
  // Turn all zones off
  for (int x = 0; x < sizeof(zoneList); x++) {
    digitalWrite(zoneList[x], LOW);
  }
}

void setup() {
	delay(10);
	radio.initialize(FREQUENCY,NODEID,NETWORKID);
	radio.encrypt(KEY);
	radio.promiscuous(promiscuousMode);
}

void loop() {
	// Read incoming messages
	if (radio.receiveDone() ) {
		// Extract Payload from Message
		payload = *(Payload*)radio.DATA;
		// Process message type (See Enum: MsgTypeIndex)
		switch(payload.MsgType) {
			// Process message type 
			case zoneCtrl:
				// Take action on a single zone
				// Extract zoneCtrl message
				i_zoneCtrl = *(_zoneCtrl*)payload.msg;
				

			/*
			case zoneGroupCtrl:
				// Take action on a predefined group a zones
				// Execute sequentially
			
			case: sysCtrl:
				// System control message.
				// Execute overrides to existig operation
			case sysStatus:
				// System status message
				// Used to communicate system state
			default:
				// Unknown command type
			*/	// TODO: send error response

		}
	}




}