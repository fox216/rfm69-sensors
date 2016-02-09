/*
Report Sensor
- Send status message to gateway 
- Report status based on SENSOR_HEARTBEAT
- Version 1 Sends MILLIS Message
*/

#include <RFM69.h>
#include <SPI.h>
#include <NodeMsg.h> // Load Gateway Message structure
#include <NodeConf.h>
// declare radio
RFM69 radio;
bool wd_active = false;
bool promiscuousMode = false; //set to 'true' to sniff all packets on the same network

void setup() {
	delay(10);
	radio.initialize(FREQUENCY,NODEID,NETWORKID);
	radio.encrypt(KEY);
	radio.promiscuous(promiscuousMode);

}

void blink(byte PIN, int DELAY_MS) {
	pinMode(PIN, OUTPUT);
	//times = times * 2;
	digitalWrite(PIN, HIGH);
	delay(DELAY_MS);
	digitalWrite(PIN, LOW);
}

void loop() {

	if (millis() % SENSOR_HEARTBEAT == 0) {
		payload.MsgType = 20;
		payload.MsgID = NODEID;
		o_MillsCount.mills = millis();
		memcpy(payload.msg, &o_MillsCount, sizeof(o_MillsCount));
		// NOTE: sendWithRetry will send 3 attempts or until and ACK is received.
		// Causing issue with NodeRed receiving 3 copies of the message.
		// Changing to generic send method for testing... duh
		//radio.sendWithRetry(GATEWAY, (const void*)(&payload), sizeof(payload));	
		radio.send(GATEWAY, (const void*)(&payload), sizeof(payload));	
		delay(100);
		blink(LED, 3);
	}


}

