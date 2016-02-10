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
int rxSize;
bool promiscuousMode = false; //set to 'true' to sniff all packets on the same network
int runCount = 0;
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
		// Send Heartbeat
		payload.MsgType = 10;
		o_MillsCount.mills = millis();
		memcpy(payload.msg, &o_MillsCount, sizeof(o_MillsCount));
		// NOTE: sendWithRetry will send 3 attempts or until and ACK is received.
		// Causing issue with NodeRed receiving 3 copies of the message.
		// Changing to generic send method for testing... duh
		//radio.sendWithRetry(GATEWAY, (const void*)(&payload), sizeof(payload));	
		rxSize = PAYLOAD_HEADER_SIZE + sizeof(o_MillsCount);
		radio.send(GATEWAY, (const void*)(&payload), rxSize);	
		delay(10);
		blink(LED, 5);
		runCount ++;
	} else if (millis() % SENSOR1_UPDATE_FREQUENCY == 0){
		// update interval for sensor1
		// Send sensor 1 
		payload.MsgType = 20;
		o_ReportMsg.bt = 42;
		o_ReportMsg.si = runCount;
		o_ReportMsg.ui = runCount - 5;
		o_ReportMsg.fp = runCount / 10;
		o_ReportMsg.db = runCount / runCount + runCount;
		o_ReportMsg.sc = 'K';
		memcpy(payload.msg, &o_ReportMsg, sizeof(o_ReportMsg));
		rxSize = PAYLOAD_HEADER_SIZE + sizeof(o_ReportMsg);
		radio.send(GATEWAY, (const void*)(&payload), rxSize);	
		


		blink(LED, 10);
	}


}

