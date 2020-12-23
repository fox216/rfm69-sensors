/*
RangeTest.cc

*/

#include <RFM69.h>
#include <SPI.h>


#define KEY         "thisIsEncryptKey" //has to be same 16 characters/bytes on all nodes, not more not less!
#define LED         9


#define FREQUENCY   RF69_915MHZ
#define NETWORKID     100  //the same on all nodes that talk to each other
#define RECEIVER      32    //unique ID of the gateway/receiver
#define SENDER        42
// #define NODEID        SENDER  //change to "SENDER" if this is the sender 
#define NODEID        RECEIVER  //change to "SENDER" if this is the sender 
RFM69 radio;
int counter =0;

void Blink(byte PIN, byte DELAY_MS, byte loops) {
  for (byte i=0; i<loops; i++)
  {
    digitalWrite(PIN,HIGH);
    delay(DELAY_MS);
    digitalWrite(PIN,LOW);
    delay(DELAY_MS);
  }
}


void setup()  {
  delay( 3000 ); // power-up safety delay
  Serial.begin(115200);

  // Initialize Radio 
  radio.initialize(FREQUENCY, NODEID, NETWORKID);
  radio.encrypt(KEY);
  // Gateway is the receiver
}


void loop() {
  if (NODEID == SENDER) {
  	// send a ping every second
  	radio.sendWithRetry(RECEIVER, "Hi", 2);
  	Blink(LED, 100, 3);
  	delay(2000);
  } else {
  	// execute reciever logic
  	if (radio.receiveDone()) {
  		counter +=1;
  		Serial.print("[ ");
  		Serial.print(radio.SENDERID);
  		Serial.print(" ]");
  		Serial.print((char*)radio.DATA);
  		Serial.print(" <RX_RSSI:");
  		Serial.print(radio.RSSI);
  		Serial.print(">");
    	Serial.println();
    	    //check if sender wanted an ACK
	    if (radio.ACKRequested()){
	      radio.sendACK();
	      Serial.print(counter );
	      Serial.println(" - ACK sent");
	    }
  	}
  }
}