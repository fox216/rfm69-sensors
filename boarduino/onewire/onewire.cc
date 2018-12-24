/*
 *   DS2438TemperatureAndVoltage
 *
 *   This example demonstrates the use of the DS2438 Library to read temperature and
 *   voltage from a Dallas Semiconductor DS2438 battery monitor using the Arduino
 *   OneWire library.
 *
 *   by Joe Bechter
 *
 *   (C) 2012, bechter.com
 *
 *   All files, software, schematics and designs are provided as-is with no warranty.
 *   All files, software, schematics and designs are for experimental/hobby use.
 *   Under no circumstances should any part be used for critical systems where safety,
 *   life or property depends upon it. You are responsible for all use.
 *   You are free to use, modify, derive or otherwise extend for your own non-commercial purposes provided
 *       1. No part of this software or design may be used to cause injury or death to humans or animals.
 *       2. Use is non-commercial.
 *       3. Credit is given to the author (i.e. portions © bechter.com), and provide a link to the original source.
 *
 */

// // #include <Arduino.h>
// #include <OneWire.h>
// #include <DS2438.h>

// // define the Arduino digital I/O pin to be used for the 1-Wire network here
// const uint8_t ONE_WIRE_PIN = 2;

                                                                                                         


// // define the 1-Wire address of the DS2438 battery monitor here (lsb first)
// uint8_t DS2438_address[] = { 0x14, 0x0D, 0xD4, 0x69, 0x02, 0x00, 0x00, 0x48 };

// OneWire ow(ONE_WIRE_PIN);
// DS2438 ds2438(&ow, DS2438_address);

// void setup() {
//     Serial.begin(115200);
//     ds2438.begin();
// }

// void loop() {
//     ds2438.update();
//     if (ds2438.isError()) {
//         Serial.println("Error reading from DS2438 device");
//     } else {
//         Serial.print("Temperature = ");
//         Serial.print(ds2438.getTemperature(), 1);
//         Serial.print("C, Channel A = ");
//         Serial.print(ds2438.getVoltage(DS2438_CHA), 1);
//         Serial.print("v, Channel B = ");
//         Serial.print(ds2438.getVoltage(DS2438_CHB), 1);
//         Serial.println("v.");
//     }
//     delay(500);
// }


// Address=14 D D4 69 2 0 0 48                                                                                                       
// Address CRC is correct.  

#include <OneWire.h>
#include <DallasEPROM.h>

OneWire onew(2);  // on pin 4
DallasEPROM de(&onew);

void setup() {
  Serial.begin(115200);
}

void loop() {
  byte buffer[32];  // Holds one page of data
  int status;

  // Search for the first compatible EPROM/EEPROM on the bus.
  // If you have multiple devices you can use de.setAddress()
  de.search();

  // Print out the 1-wire device's 64-bit address
  Serial.print("Address=");
  for(int i = 0; i < 8; i++) {
    Serial.print(de.getAddress()[i], HEX);
    Serial.print(" ");
  }
  Serial.println("");

  if (de.getAddress()[0] == 0x00) {
    Serial.println("No device was found!");
  } else {
    if (de.validAddress(de.getAddress())) {
      Serial.println("Address CRC is correct.");

      // Uncomment to write to the first page of memory
      //strcpy((char*)buffer, "allthingsgeek.com");
      //if ((status = de.writePage(buffer, 0)) != 0) {
        //sprintf((char*)buffer, "Error writing page! Code: %d", status);
        //Serial.println((char*)buffer);
      //}

      // Read the first page of memory into buffer
      if ((status = de.readPage(buffer, 0)) == 0) {
        Serial.println((char*)buffer);
      } else {
        sprintf((char*)buffer, "Error reading page! Code: %d", status);
        Serial.println((char*)buffer);
      }
    } else {
      Serial.println("Address CRC is wrong.");
    }
  }
  Serial.println("");

  delay(3000);
}

