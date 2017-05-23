#include "Arduino.h"
void setup();
void loop();
// rfm -led3.cc
#include <RFM69.h>
#include <SPI.h>
#include <NodeMsg.h>
#include <NodeConf.h>
#include <Sensors.h>
//#define DEBUG_SERIAL
// Initialize Radio
RFM69 radio;
bool readyToXmit = false;
bool flashLed1 = false;
int msgSize = 0;

void setup() {
	#ifdef DEBUG_SERIAL
	Serial.begin(SERIAL_BAUD);
	// Wait for serial to initialize
	//while(! Serial) {}
	#endif
	radio.initialize(FREQUENCY, NODEID, NETWORKID);
	radio.encrypt(KEY);
  	pinMode(LED1, OUTPUT);

}

void Blink(byte PIN, int DELAY_MS) {
  pinMode(PIN, OUTPUT);
  digitalWrite(PIN,HIGH);
  delay(DELAY_MS);
  digitalWrite(PIN,LOW);
}
bool flashLed1_set = false;
unsigned long flashLed1_calc;
void loop() {
	if (flashLed1) {
		if (millis() % Sensor_15.led1_mode == 0 and (micros() - flashLed1_calc) > Sensor_15.led1_mode - 100 ) { //FIXME
			digitalWrite(LED1, !digitalRead(LED1));
			// flashLed1_set = true;
			flashLed1_calc = micros();
		} 
		// else {
		// 	if (micros() - flashLed1_calc > 500 ) {
		// 		flashLed1_calc = true;
		// 	}
		// }
	}
	if (radio.receiveDone() ) {
		// process incloming message
		// cast message data into nodeMsg structure
		nodeMsg = *(_NodeMsg*)radio.DATA;
		
	 	if (nodeMsg.TypeID == 15) {
			// echo '{"node":"44","meth":2,"type":5,"data":[10,1,10,1]}' > /dev/ttyGW2
			// cho '{"node":"44","meth":2,"type":5,"data":[10,1,10,0]}' > /dev/ttyGW2
			// echo '{"node":"44","meth":2,"type":5,"data":[10,1,10,0]}' > /dev/ttyGW2
			Sensor_15 = *(_Sensor_15*)nodeMsg.MsgPayload;
			// set static 
			if (Sensor_15.led1_mode == 1) {
			  	flashLed1 = false;
			  	digitalWrite(LED1,HIGH);
			} else if (Sensor_15.led1_mode == 2) {
				// toggle 
				flashLed1 = false;
				digitalWrite(LED1, !digitalRead(LED1));
			} else {
				// power off
			  	flashLed1 = false;
			  	digitalWrite(LED1,LOW);
			}
			// set flash rate
			if (Sensor_15.led1_mode > 500) {
				flashLed1 = true;
			}
			
		}
	} else {
		// post message to gateway (Heartbeat Example)
		if (millis() % SENSOR_HEART_BEAT == 0) {
			#ifdef DEBUG_SERIAL
			Serial.println("Sending Heartbeat");
			#endif
	  		nodeMsg.NodeID = 1;
	  		nodeMsg.Method = 4;
	  		nodeMsg.TypeID = 100;

	  		Sensor_100.m1 = 41;
	  		Sensor_100.runCount +=1;
	  		Sensor_100.m2 = 41;
	  		Sensor_100.MillSecs = millis();

	  		memcpy(nodeMsg.MsgPayload, &Sensor_100, sizeof(_Sensor_100));
	  		msgSize = MSG_HEADER_SZ + sizeof(_Sensor_100);
	  		readyToXmit = true;
		}
		if (readyToXmit) {
			radio.send(nodeMsg.NodeID, (const void*)(&nodeMsg), msgSize);
			Blink(9, 100);
			readyToXmit = false;
		}	
	} 
}