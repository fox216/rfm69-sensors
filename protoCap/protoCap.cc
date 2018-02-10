/*
Prototype Boarduino Capaitive water sensor
2018-02-09
Author: Kevin Fox
*/

#include <CapacitiveSensor.h>

// Capacitive sensor connected to pins 9 and 12
// Pin 9 connected to 1.8 Ohm resistor
CapacitiveSensor	cs_WaterLevel = CapacitiveSensor(9, 12);



void setup() {
	// Setup sensor
	cs_WaterLevel.set_CS_AutocaL_Millis(0xFFFFFFFF);
	// Initialize Serial Port
	Serial.begin(115200);
}


void loop() {
	long start = millis();
	long WaterLevel = cs_WaterLevel.capacitiveSensor(30);

	Serial.print(millis() - start);
	Serial.print("\t");
	Serial.print(WaterLevel);
	Serial.println();

	delay(500);

}

