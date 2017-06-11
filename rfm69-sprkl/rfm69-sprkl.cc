// rfm-json-sprkl
#include <RFM69.h>
#include <SPI.h>
// #include <GatewayMsg.h> // Load Gateway Message structure:Task
#include <NodeMsg.h>
#include <NodeConf.h>
#include <Sensors.h>

RFM69 radio;
bool readyToXmit = false;
int msgSize = 0;

void disableAllZones(){
  // Turn all zones off
  for (int x = 0; x < sizeof(zoneList); x++) {
    digitalWrite(zoneList[x], LOW);
  }
  sysState.zoneActive = false;
}

void setup()  {
	#ifdef DEBUG_SERIAL
	Serial.begin(SERIAL_BAUD);
	#endif
	// Initialize 
	radio.initialize(FREQUENCY, NODEID, NETWORKID);
	radio.encrypt(KEY);
  //	pinMode(LED1, OUTPUT);
  // Set IO direction for sprinkler outputs
	pinMode(3, OUTPUT);
	pinMode(4, OUTPUT);
	pinMode(5, OUTPUT);
	pinMode(6, OUTPUT);
	pinMode(7, OUTPUT);
	pinMode(8, OUTPUT);
	pinMode(14, OUTPUT);
	pinMode(15, OUTPUT);
	pinMode(16, OUTPUT);
	pinMode(17, OUTPUT);

	// When mote starts up force all zones off
	disableAllZones();
}  // END SETUP

void enableZone(byte Zone) {
 	// Function controls an individual zone
	// 
	// Disable zones (if running)
	disableAllZones();
	// Dwell time between zones
	delay(SPRKL_DWELL_TIME);
	// TODO Add switch to access only defined zones in ZoneIoMap
	digitalWrite(Zone, HIGH);
	// Enable cycle scanner
	sysState.zoneActive = true;
	// Reset Cycle Counter
	sysState.cycleCount = 0;

}

// void enableProg() {
// 	// run program
// 	sysState.zoneAcc = sizeof(&sysState.progPtr);
// 	for (byte thisZone = 0; thisZone >= sysState.zoneAcc; thisZone ++ ) {
// 		// Enable zone in program
// 		enableZone(thisZone);
// 	}

// }

// void zoneControl(_Sensor_zoneCtrl* zone) {
// }

void loop() {
	// Process incoming message / action
	if (radio.receiveDone() ) {
		// Convert radiio data to sensor message
		nodeMsg = *(_NodeMsg*)radio.DATA;
		switch (nodeMsg.TypeID) { // see enum MsgTypeIndex
			case zoneCtrl:
				// Message type is for single zone control
			  // cast to structure
			  sysState.runMode = nodeMsg.TypeID;
				Sensor_zoneCtrl = *(_Sensor_zoneCtrl*)nodeMsg.MsgPayload;
				//zoneControl(&Sensor_zoneCtrl); 
				enableZone(zoneList[Sensor_zoneCtrl.zoneNum]);
				// set cycle limit (number of seconds)
				sysState.cycleLimit = Sensor_zoneCtrl.runSeconds;

				// Enable system
				// envokes cycle checker
				sysState.sysActive = true;
				break;
			case progCtrl:
				// Run a program
				// set run mode
				sysState.runMode = nodeMsg.TypeID;
				sysState.cycleLimit = Sensor_progCtrl.runSeconds;
				Sensor_progCtrl = *(_Sensor_progCtrl*)nodeMsg.MsgPayload;
				switch (Sensor_progCtrl.progNum) {
					// set program pointer
					case 100:
					  sysState.progArrSize = sizeof(allList);
						sysState.progPtr = allList;
						sysState.runProgram = true;
					break;
					case 101:
					  sysState.progArrSize = sizeof(frontList);
						sysState.progPtr = frontList;
						sysState.runProgram = true;

					break;
					case 102:
					  sysState.progArrSize = sizeof(backList);
						sysState.progPtr = backList;
						sysState.runProgram = true;
					break;
					default:
						// unknown program
						disableAllZones();
						sysState.sysActive = false;
					break;
				}
				if (sysState.runProgram) {
					// Start first item in list
					sysState.zoneAcc = 0;
					enableZone(*(sysState.progPtr + sysState.zoneAcc));
				}
				break; // End progCtrl Case
		}
	}
	if (sysState.sysActive) {
		// Monitor system status
		if (millis() % SENSOR_SCAN_PERIOD == 0 ) {
			// Add scan delay (debounce) for timing issue
			delay(SCAN_DEBOUNCE_TIME);
			// Review status each interval
			// Increment the cycle counter
			sysState.cycleCount ++;
			if (sysState.cycleCount >= sysState.cycleLimit) {
				// Disable system when count limit is reached
				switch(sysState.runMode) {
					case zoneCtrl:
						disableAllZones();
						sysState.sysActive = false;
						break;
					case progCtrl:
						// Cycle through items in pointer array
					  // Increment zone accumulator
						sysState.zoneAcc++;
						if (sysState.zoneAcc >= sysState.progArrSize) {
							// program complete
							disableAllZones();
							sysState.runProgram = false;
						} else {
							// enable next zone in program list
							enableZone(*(sysState.progPtr + sysState.zoneAcc));
						}
					break;
				}
			}
		}
	}


} // End Loop

