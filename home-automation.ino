#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <Servo.h>

#define BLYNK_TEMPLATE_ID "TMPLIdZLtuF7"
#define BLYNK_DEVICE_NAME "Home Automation"
#define BLYNK_AUTH_TOKEN "MHepzfMcrqzc9ezENUaEjDI2qgHK5Nuq"

char auth[] = "MHepzfMcrqzc9ezENUaEjDI2qgHK5Nuq";//Enter you blynk auth token
char ssid[] = "realme7";//Enter your WIFI name
char pass[] = "joker@123";//Enter your WIFI password

//Define ESP8266 pins
#define Flame D0
#define LED1 D1
#define LED2 D2
#define LED3 D3
#define LED4 D4
#define IR D5
#define LED5 D6
//#define Servo D7  GPIO13
#define Buzzer D8
#define Gas A0
int gas = 0;
int sensorThres = 100;
Servo servo;

BLYNK_WRITE(V1){
  servo.write(param.asInt());
  servo.attach(D7, 500, 2400);
}

void setup()
{
  pinMode(IR, INPUT);
  pinMode(Buzzer, OUTPUT);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);
  pinMode(LED5, OUTPUT);
  pinMode(Flame, INPUT);
  pinMode(Gas, INPUT);
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass, "blynk.cloud", 80); //Initialize the Blynk library
}

void loop() {

  // IR Sensor
  int ir = digitalRead(IR);
  if(ir == 0)
  {
    digitalWrite(Buzzer, HIGH);
    digitalWrite(LED1, HIGH);
    Blynk.logEvent("object_detection", "Alert, An Object is Detected.");
    Blynk.email("aryansky333@gmail.com", "Object Detection", "Alert, An Object is Detected.");
    Serial.println("Object Detected!");
  }
  else{
    digitalWrite(Buzzer, LOW);
    digitalWrite(LED1, LOW);
    Serial.println("Negative Object Detection.");
  }

  // Flame Sensor
  int flame = digitalRead(Flame);
  if(flame == 0)
  {
    digitalWrite(LED1, HIGH);
    tone(Buzzer, 3000); // Send 1KHz sound signal...
    delay(1000);        // ...for 1 sec
    Blynk.logEvent("fire", "Warning, Fire Detected! Please take immediate action.");
    Blynk.email("aryansky333@gmail.com", "Fire Warning", "Warning, Fire Detected! Please take immediate action.");
    Serial.println("Fire Detected!");
  }
  else{
    digitalWrite(Buzzer, LOW);
    digitalWrite(LED1, LOW);
    Serial.println("Negative Fire Detection.");
  }

  // MQ2 Gas Sensor
  int gas = analogRead(Gas);
  Blynk.virtualWrite(V2, gas);
  if (gas > 650)
  {
      digitalWrite(Buzzer, HIGH);
      digitalWrite(LED1, HIGH);
      Serial.println("Gas Leakage Detected!");
      Blynk.logEvent("gas","Warning, Gas Leakage Detected! Please take appropriate action.");
      Blynk.email("aryansky333@gmail.com", "Gas Leakage Warning", "Warning, Gas Leakage Detected! Please take appropriate action.");
    }
    else {
      digitalWrite(Buzzer, LOW);
      digitalWrite(LED1, LOW);
      Serial.println("Negative Gas Leak.");
    }
    Serial.print("Gas Value: ");
    Serial.println(gas);
    Serial.println("");
    delay(1000);

  //Run the Blynk library
  Blynk.run();
}
