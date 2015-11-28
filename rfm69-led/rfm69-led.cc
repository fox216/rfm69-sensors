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

void LedState(byte PIN, byte state) {
	pinMode(PIN, OUTPUT);
	if (state > 0) {
		digitalWrite(PIN, HIGH);
	} else {
		digitalWrite(PIN, LOW);
	}
}


void loop() {

	// Process message from Gateway...
	if ( radio.receiveDone() ) {
		//blink(LED,5);
		payload = *(Payload*)radio.DATA;
		switch(payload.MsgType) {
			// Find matching message handler
			case LedMsg:
				i_LedMsg = *(_LedMsg*)payload.msg;
				LedState(i_LedMsg.led, i_LedMsg.state);
			default:
				blink(LED, 5);
		}
	}
	// report LED Status
	// report last sensor change
	if (millis() % SENSOR_REPORT_PERIOD == 0) {
		// Send Status Message
		// Simple form
		payload.MsgType = 20;
		payload.MsgID = 99;
		if (o_LedMsg.led != 0 ) {
			// Send status of last LED set
			o_LedMsg.led = i_LedMsg.led; 
			o_LedMsg.state = digitalRead(o_LedMsg.led)
			
		} else {
			// Send LED status indicating nothing is set. 
			// Status = Uninitialized....
			o_LedMsg.led = 254; 
			o_LedMsg.state = 254;
		}
		memcpy(payload.msg, &o_LedMsg, sizeof(o_LedMsg));
		radio.sendWithRetry(sMsg.NodeID, (const void*)(&payload), sizeof(payload));
	}

	if (millis() % SENSOR_HEARTBEAT == 0) {
		payload.MsgType = 20;
		payload.MsgID = 42;
		o_MillsCount.mills = millis();
		memcpy(payload.msg, &o_MillsCount, sizeof(o_MillsCount));
		radio.sendWithRetry(sMsg.NodeID, (const void*)(&payload), sizeof(payload));	
	}


}




