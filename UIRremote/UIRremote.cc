/*

Universal IR remote sensor

*/

#include <IRremote.h>

#define SamsungPowerOnOff 0xE0E040BF
#define SamsungVolUp      0xE0E0E01F   
#define SamsungVolDown    0xE0E0D02F   

// NEC Device
#define JBL_SB_PowerOnOff 0x212EFF00 // 32 Bit
#define JBL_SB_VolUp      0x10EE31C 
#define JBL_SB_VolDown    0x10E13EC
#define JBL_SB_HDMI2      0x10ECF30 // HDMI2
#define JBL_SB_HDMI1      0x10E4FB0 // HDMI1
#define JBL_SB_MUTE       0x10E837C // Mute

IRsend irsend;

bool StateOnOff = false;

void setup() {
  delay(5000); // Startup dalay

}

void loop() {

  // Turn Power On
  // for (int i = 0; i < 3; i++) {

    irsend.sendNEC(JBL_SB_PowerOnOff, 32);
    // delay(40);
  // }
  delay(2000);






}