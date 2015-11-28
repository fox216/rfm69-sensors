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
				i_LedMsg = *(I_LedMsg*)payload.msg;
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

	}


}




