
#include <RFM69.h>
#include <SPI.h>
// #include <GatewayMsg.h> // Load Gateway Message structure:Task
#include <NodeMsg.h>
#include <NodeConf.h>
#include <Sensors.h>
// Initialize Radio
#define DEBUG_SERIAL

RFM69 radio;

void setup() {
	#ifdef DEBUG_SERIAL
	Serial.begin(SERIAL_BAUD);
	// Wait for serial to initialize
	while(! Serial) {}
	#endif
	radio.initialize(FREQUENCY, NODEID, NETWORKID);
	radio.encrypt(KEY);
  	pinMode(LED1, OUTPUT);
  	pinMode(LED2, OUTPUT);

}

void loop() {
	if (radio.receiveDone() ) {
		// process incloming message
		// cast message data into nodeMsg structure
		nodeMsg = *(_NodeMsg*)radio.DATA;
		
		//memcpy(Sensor_t6, *(_Sensor_t6*)&nodeMsg.MsgPayload, sizeof(Sensor_t6));
		#ifdef DEBUG_SERIAL
		Serial.print("Received Message from Node -> ");
		Serial.println(radio.SENDERID);

		Serial.print("Method: ");
		Serial.println(nodeMsg.Method);

		Serial.print("Sensor Type: ");
		Serial.println(nodeMsg.TypeID);

		// Serial.print("Meta Map: ");
		// Serial.println(nodeMsg.PayloadDataMap);
		if (nodeMsg.TypeID == 6 ) {
			Sensor_t6 = *(_Sensor_t6*)nodeMsg.MsgPayload;
			Serial.print("b1 = ");
			Serial.println(Sensor_t6.b1);
			Serial.print("L1 = ");
			Serial.println(Sensor_t6.L1);
			Serial.print("f1 = ");
			Serial.println(Sensor_t6.f1);
			Serial.print("f2 = ");
			Serial.println(Sensor_t6.f2);
			Serial.print("i1 = ");
			Serial.println(Sensor_t6.i1);
		} else if (nodeMsg.TypeID == 5) {
			// echo '{"node":"44","meth":2,"type":5,"data":[10,1,10,1]}' > /dev/ttyGW2
			// cho '{"node":"44","meth":2,"type":5,"data":[10,1,10,0]}' > /dev/ttyGW2
			// echo '{"node":"44","meth":2,"type":5,"data":[10,1,10,0]}' > /dev/ttyGW2
			Sensor_t5 = *(_Sensor_t5*)nodeMsg.MsgPayload;

			if (Sensor_t5.led1 == 1) {
			  digitalWrite(LED1,HIGH);
			} else {
			  digitalWrite(LED1,LOW);

			}
			if (Sensor_t5.led2 == 1) {
			  digitalWrite(LED2,HIGH);
			} else {
			  digitalWrite(LED2,LOW);
				
			}
		}


		#endif

	} 



}