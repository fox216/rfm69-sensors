// discover_onewire.cc

#include <OneWire.h>

OneWire ow(5);  // on pin 2

void setup() {
  Serial.begin(115200);
}

void loop() {
  byte buffer[32];  // Holds one page of data
  int status;
  byte i;
  byte present = 0;
  byte data[12];
  byte addr[8];


	ow.search(addr);

	switch(addr[0]) {
		case 0x81:
			Serial.println("Serial ID Button");
		break;
		case 0x28:
			Serial.println("Programmable Thermometer (18B20)");
		break;
		case 0x26:
			Serial.println("Smart Battery Monitor (2438)");
		break;
		case 0x14:
			Serial.println("256 EEPROM (2430A)");
		break;
		default:
			Serial.print("Unknown OneWire Device: ");
			Serial.println(addr[0], HEX);
		break;
	}


  // Print out the 1-wire device's 64-bit address
  Serial.print("Address=");
  for(int i = 0; i < 8; i++) {
    Serial.print(addr[i], HEX);
    Serial.print(" ");
  }
  Serial.println("");

  

}

/*

Address=28 18 65 C9 0 0 0 8D 
Address=14 D D4 69 2 0 0 48 
Address=26 33 B2 6B 0 0 0 1D 
*/
