/* Libary */
#include <WiFiManager.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>

/* Pin */
#define Sensor 32
#define Relay 2

/* Call */
WiFiClient espClient;
PubSubClient mqtt(espClient);

/* Value */
int sensor_Value = 0;
int Soil_Value = 0;
int check_time;

/* Devide Id */
String deviceid = "pooh_project";

/* MQTT Connect */
const char* mqttServer = "kraiwich.thddns.net";
const int mqttPort = 4441;
const char* mqttUser = "kraiwich";
const char* mqttPassword = "kraiwich1234";
char mqtt_name_id[] = "";
const char* pubTopic = "kraiwich/project_pooh";

/* Json config */
StaticJsonDocument<256> doc;
char buffer[256];

/* Millis */
unsigned long period = 1800000; 
unsigned long last_time = 0; 

void setup()
{
  Serial.begin(115200);
  pinMode(Relay, OUTPUT);
  delay(200);
  Setup_WM();
  delay(200);
  MQTT_connect();
  delay(200);
}

void loop()
{
  if (!mqtt.connected()) {
    Serial.println("---Reconnect MQTT ---");
    MQTT_reconnect();
  }
  mqtt.loop();
  Read_SOIL();
  working();
  Serial.println("=================");
  send_data();
  Serial.println("=================");
}
