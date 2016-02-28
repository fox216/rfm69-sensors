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
int rxSize;


void setup() {
	// Setup Serial for Debug
	if (DEBUG_ENABLED == 1){
		Serial.begin(SERIAL_BAUD);
		delay(10);
	}
	// Setup Radio
	radio.initialize(FREQUENCY,NODEID,NETWORKID);
	radio.encrypt(KEY);
	radio.promiscuous(promiscuousMode);
}


void disableAllZones(){
  // Turn all zones off
  for (int x = 0; x < sizeof(zoneList); x++) {
    digitalWrite(zoneList[x], LOW);
  }
  sysState.sysActive = false;
}

void enableZone(byte Zone) {
	// verify all zones are off
	disableAllZones();
	// Dwell time between zones
	delay(SPRKL_DWELL_TIME);
	// TODO Add switch to access only defined zones in ZoneIoMap
	digitalWrite(Zone, HIGH);
	// Enable cycle scanner
	sysState.sysActive = true;
	// Reset Cycle Counter
	sysState.cycleCount = 0;

}

void blink(byte PIN, int DELAY_MS) {
	pinMode(PIN, OUTPUT);
	//times = times * 2;
	digitalWrite(PIN, HIGH);
	delay(DELAY_MS);
	digitalWrite(PIN, LOW);
}


void setCycle(byte CycleSelect) {
	switch(CycleSelect) {
		case min2:
			sysState.cycleLimit = 120;
			break;
		case min5:
			sysState.cycleLimit = 300;
			break;
		case min10:
			sysState.cycleLimit = 600;
			break;
		default:
			// Set deafult value ot 10 seconds
			sysState.cycleLimit = 10;	// Set to 10 seconds for testing............
	}
	/* DEBUG
	Serial.print("Cycle Limit: ");
	Serial.println(sysState.cycleLimit);
	*/
}

void sendStatus() {
	Serial.print("Sending status message! ");
	// send status message 
	payload.MsgType = sysStatus;
	o_SysStatus.zone 			= sysState.currentZone;
	o_SysStatus.state 			= sysState.sysCurState; 
	o_SysStatus.progName 		= sysState.progName;
	o_SysStatus.percComplete 	= sysState.cycleCount / sysState.cycleLimit;
	// Pack payload into array for transmission
	memcpy(payload.msg, &o_SysStatus, sizeof(o_SysStatus));
	// Calc payload size
	rxSize = PAYLOAD_HEADER_SIZE + sizeof(o_SysStatus);
	radio.send(GATEWAY, (const void*)(&payload), rxSize);	
}


void loop() {
	// Read incoming messages
	if (radio.receiveDone() ) {
		// Extract Payload from Message
		payload = *(Payload*)radio.DATA;
		// Process message type (See Enum: MsgTypeIndex)
		switch(payload.MsgType) {
			// Process message type
			if (DEBUG_ENABLED == 1) {
				// DEBUG
				Serial.print("Executing Message Type: ");
				Serial.println(payload.MsgType);
			} 
			case zoneCtrl:
				// #20
				// Take action on a single zone
				// Extract zoneCtrl message
				i_zoneCtrl = *(_zoneCtrl*)payload.msg;
				sysState.progName = 'X'; // No program, single run

				delay(20);
				if (DEBUG_ENABLED == 1) {
					Serial.print("Cycle Select: ");
					Serial.println(i_zoneCtrl.cycleSelect);
				}	
				setCycle(i_zoneCtrl.cycleSelect);
				enableZone(i_zoneCtrl.zone);
				break;
			case runProg:
				// #30
				// Take action on a predefined group a zones
				// Execute sequentially
				i_runProg = *(_runProg*)payload.msg;
				// Process progarm logic in RUNTIME section
				// Verify input value
				switch(i_runProg.program) {
					// Valid program modes
					case 'A':
					case 'F':
					case 'B':
						sysState.progName = i_runProg.program; 
						if (DEBUG_ENABLED == 1) {
							Serial.print("Executing Program: ");
							Serial.println(sysState.progName);
						}
					break;
					default:
						if (DEBUG_ENABLED == 1) {
							Serial.print("ERROR -> Invalid Program: ");
							Serial.println(i_runProg.program);
						}
						// Set program name to reserved, invalid type.
						// Used by processing logic to exclude program run.
						sysState.progName = 'x';
				}
				break;
			case sysCtrl:
				// #40
				// System control message.
				// Execute overrides to existig operation
				i_SysCtrl = *(_SysCtrl*)payload.msg;
				// Set system state
				if (DEBUG_ENABLED == 1) {
					Serial.print("Setting Execution Mode: ");
					Serial.println(sysState.sysCurState);
				}
				// Validate input
				switch(i_SysCtrl.state) {
					case 'R':
					case 'C':
					case 'P':
						sysState.sysCurState = i_SysCtrl.state; 
					default:
						// State unchanged...
						if (DEBUG_ENABLED == 1) {
							Serial.print("ERROR -> Invalid State: ");
							Serial.println(i_SysCtrl.state);
						}
						// Place holder...
						sysState.sysCurState = sysState.sysCurState;
				}
				break;
			case sysStatus:
				// #50
				// Send status after receiving header. Ignores payload.
				// System status message
				// Used to communicate system state
				if (DEBUG_ENABLED == 1) {
					Serial.print("Executing Message Type: ");
					Serial.println(payload.MsgType);
				}
				sendStatus();
				break;
			default:
				// Unknown command type
				if (DEBUG_ENABLED == 1) {
					Serial.print("ERROR -> Unknown Message Type: ");
					Serial.println(payload.MsgType);
				}
		}
	}
	//
	// RUNTIME Section -> Scan Cycle
	//
	if (sysState.sysActive) {
		// Only scan if system is active
		if (millis() % SENSOR_SCAN_PERIOD == 0) {
			// Scan every second
			if (sysState.cycleCount > sysState.cycleLimit) {
				disableAllZones();
			} else {
				// increment cycle counter
				sysState.cycleCount ++;
				// Add delay time delay to avoid counting all cycles
				delay(10);
			}
			
			if (DEBUG_ENABLED == 1) {
				//DEBUG
				Serial.print("Count: ");
				Serial.print(sysState.cycleCount);
				Serial.print(" Limit: ");
				Serial.println(sysState.cycleLimit);
			}
			
		}
	}
	//
	// Send heartbeat message
	// Keep alive message for gateway.
	//
	if (millis() % SENSOR_HEARTBEAT == 0) {
		// Set payload
		payload.MsgType = heartbeat;
		o_heartbeat.mills = millis();
		memcpy(payload.msg, &o_heartbeat, sizeof(o_heartbeat));
		rxSize = PAYLOAD_HEADER_SIZE + sizeof(o_heartbeat);
		radio.send(GATEWAY, (const void*)(&payload), rxSize);	
		blink(LED, 150);
	}
}