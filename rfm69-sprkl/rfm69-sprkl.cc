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

void setup()  {
	#ifdef DEBUG_SERIAL
	Serial.begin(SERIAL_BAUD);
	#endif
	radio.initialize(FREQUENCY, NODEID, NETWORKID);
	radio.encrypt(KEY);
  	pinMode(LED1, OUTPUT);

}


void loop() {


}