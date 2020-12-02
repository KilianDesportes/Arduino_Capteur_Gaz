#include <TheThingsNetwork.h>
#include <SoftwareSerial.h>

const char *devAddr = "26011460";
const char *nwkSKey = "6A9A748C8D3FD8FABF0676303586CF2F";
const char *appSKey = "6C543B9F868CD324503F11C92267081B";

SoftwareSerial loraSerial(10, 11);
#define debugSerial Serial

// Replace REPLACE_ME with TTN_FP_EU868 or TTN_FP_US915
#define freqPlan TTN_FP_EU868

TheThingsNetwork ttn(loraSerial, debugSerial, freqPlan);

#define LED_PIN 13

void led_on()
{
  digitalWrite(LED_PIN, HIGH);
}

void led_off()
{
  digitalWrite(LED_PIN, LOW);
}

void message(const uint8_t *payload, size_t size, port_t port)
{
  debugSerial.println("-- MESSAGE");
  debugSerial.print("Received " + String(size) + " bytes on port " + String(port) + ":");

  for (int i = 0; i < size; i++)
  {
    debugSerial.print(" " + String(payload[i]));
  }

  debugSerial.println();
 
  if (payload[0] == 1){led_on();} else {led_off();}  
}


void setup()
{

  pinMode(LED_PIN, OUTPUT);
  
  loraSerial.begin(9600);
  debugSerial.begin(9600);

  // Wait a maximum of 10s for Serial Monitor
  while (!debugSerial && millis() < 10000)
    ;

  debugSerial.println("-- PERSONALIZE");
  ttn.personalize(devAddr, nwkSKey, appSKey);

  //For downlink
  ttn.onMessage(message);

  debugSerial.println("-- STATUS");
  ttn.showStatus();
}

void loop()
{
  debugSerial.println("-- LOOP");

  // Prepare payload of 1 byte to indicate LED status
  byte payload[1];
  payload[0] = (digitalRead(LED_BUILTIN) == HIGH) ? 1 : 0;

  // Send it off
  ttn.sendBytes(payload, sizeof(payload));

  delay(10000);
}
