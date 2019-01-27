// Tower Garden Sensor

#include <NodeMsg.h>
#include <NodeConf.h>
#include <Sensors.h>
// Sensor capabilities
#include <RFM69.h>
#include <SPI.h>
#include <OneWire.h>

RFM69 radio;
bool 	readyToXmit = false;
int 	msgSize = 0;

void setup()  {
  delay( 3000 ); // power-up safety delay
  Serial.begin(115200);

  // Initialize Radio 
  radio.initialize(FREQUENCY, NODEID, NETWORKID);
  radio.encrypt(KEY);


}// END SETUP

void loop() {
  // Process incoming message / action
  if (radio.receiveDone() ) {
    // Convert radiio data to sensor message
    nodeMsg = *(_NodeMsg*)radio.DATA;
    switch(nodeMsg.TypeID) {
      case patternCtrl:
      break;
    }
  } // END MSG Processing
  // raw counter
  switch 

}