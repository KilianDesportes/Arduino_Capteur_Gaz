#include <TheThingsNetwork.h>
#include <SoftwareSerial.h>

SoftwareSerial loraSerial(10, 11);

#define debugSerial Serial

// Replace REPLACE_ME with TTN_FP_EU868 or TTN_FP_US915
//#define freqPlan REPLACE_ME
#define freqPlan TTN_FP_EU868

TheThingsNetwork ttn(loraSerial, debugSerial, freqPlan);

void setup()
{
  loraSerial.begin(9600);
  debugSerial.begin(9600);

  String data = "";
debugSerial.println("demarre");
for (int i= 0; i<10 && data == ""; i++)
{ 
  loraSerial.write((byte)0x00);
  loraSerial.write(0x55);
  loraSerial.println();
  loraSerial.println("sys get ver");
  data = loraSerial.readStringUntil('\n');
  delay(1000);
} 
debugSerial.println("fin demarre");  
}

void loop()
{
  debugSerial.println("Device Information");
  debugSerial.println();
  ttn.showStatus();
  debugSerial.println();
  debugSerial.println("Use the EUI to register the device for OTAA");
  debugSerial.println("-------------------------------------------");
  debugSerial.println();

  delay(10000);
}
