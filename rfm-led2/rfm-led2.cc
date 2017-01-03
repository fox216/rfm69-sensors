
#include <RFM69.h>
#include <SPI.h>
// #include <GatewayMsg.h> // Load Gateway Message structure:Task
#include <NodeMsg.h>
#include <NodeConf.h>
#include <Sensors.h>
// Initialize Radio
//#define DEBUG_SERIAL
// Sensor_t100.runCount = 0;
RFM69 radio;
bool readyToXmit = false;
int msgSize = 0;
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

void Blink(byte PIN, int DELAY_MS) {
  pinMode(PIN, OUTPUT);
  digitalWrite(PIN,HIGH);
  delay(DELAY_MS);
  digitalWrite(PIN,LOW);
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
		#endif
		// Serial.print("Meta Map: ");
		// Serial.println(nodeMsg.PayloadDataMap);
		if (nodeMsg.TypeID == 6 ) {
			
			Sensor_t6 = *(_Sensor_t6*)nodeMsg.MsgPayload;
			#ifdef DEBUG_SERIAL
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
			#endif
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
	} else {
		// post message to gateway (Heartbeat Example)
		if (millis() % SENSOR_HEART_BEAT == 0) {
			#ifdef DEBUG_SERIAL
			Serial.println("Sending Heartbeat");
			#endif
	  		nodeMsg.NodeID = 1;
	  		nodeMsg.Method = 4;
	  		nodeMsg.TypeID = 100;

	  		Sensor_t100.m1 = 41;
	  		Sensor_t100.runCount +=1;
	  		Sensor_t100.m2 = 41;
	  		Sensor_t100.MillSecs = millis();

	  		memcpy(nodeMsg.MsgPayload, &Sensor_t100, sizeof(_Sensor_t100));
	  		msgSize = MSG_HEADER_SZ + sizeof(_Sensor_t100);
	  		readyToXmit = true;


		}
		if (millis() % HUMIDITY_READ_FREQ == 0) {
			// Read humidity sensor

			nodeMsg.NodeID = 1;
	  		nodeMsg.Method = 4;
	  		nodeMsg.TypeID = 101;

	  		Sensor_101.m1 = 40;
	  		Sensor_101.humdity = analogRead(HUMIDITY_SENSOR);
	  		// Clear Payload data
	  		//nodeMsg.MsgPayload[MAX_PAYLOAD_SIZE] = 0;
	  		//memset(nodeMsg.MsgPayload, 0, MAX_PAYLOAD_SIZE);
	  		memcpy(nodeMsg.MsgPayload, &Sensor_101, sizeof(_Sensor_101));
	  		msgSize = MSG_HEADER_SZ + sizeof(_Sensor_101);
	  		readyToXmit = true;

		}

		if (readyToXmit) {
			radio.send(nodeMsg.NodeID, (const void*)(&nodeMsg), msgSize);
			Blink(9, 100);
			readyToXmit = false;

		}	


	} 




}