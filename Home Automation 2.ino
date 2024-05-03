#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

#define BLYNK_TEMPLATE_ID "TMPLMCnVv8GC"
#define BLYNK_DEVICE_NAME "Home Automation 2"
#define BLYNK_AUTH_TOKEN "-FpqZbMMMg-E-k2Km7benu_GQkBDgSPO"

char auth[] = "-FpqZbMMMg-E-k2Km7benu_GQkBDgSPO";//Enter you blynk auth token
char ssid[] = "realme7";//Enter your WIFI name
char pass[] = "joker@123";//Enter your WIFI password.

//Define ESP8266 pins
#define Relay D0
#define LED1 D1
#define LED2 D2
#define LED3 D3
#define LED4 D4

BLYNK_WRITE(V0)
{
  bool value = param.asInt();
  // Check these values and turn the relay ON and OFF
  if (value == 1) {
    digitalWrite(Relay, LOW);
  } else {
    digitalWrite(Relay, HIGH);
  }
}

void setup()
{
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);
  pinMode(Relay, OUTPUT);
  digitalWrite(Relay, HIGH);
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass, "blynk.cloud", 80); //Initialize the Blynk library
}

void loop()
{
  Blynk.run();
}