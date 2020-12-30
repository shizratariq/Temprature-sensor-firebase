#include <ESP8266WiFi.h>
#include <SoftwareSerial.h>
#include <FirebaseArduino.h>
//#include "FirebaseESP8266.h"
#include <ESP8266HTTPClient.h>
 #include <OneWire.h>
#include <DallasTemperature.h>

#define ONE_WIRE_BUS 4

OneWire oneWire(ONE_WIRE_BUS);

DallasTemperature sensors(&oneWire);

// Set these to run example.
#define FIREBASE_HOST "health-d1813-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "BL2Sb68aYFUTtp17ihLyC7cQbit2j3axzI7zZqQT"
#define WIFI_SSID "ded"
#define WIFI_PASSWORD "12345678"

 
float Celsius = 0;
float Fahrenheit = 0;
String myString;
int sdata = 0; // The variable resistor value will be stored in sdata.
void setup()
{
  // Debug console
// sensors.begin();
  Serial.begin(9600);

  // connect to wifi.
   delay (1000);
  WiFi.begin (WIFI_SSID, WIFI_PASSWORD); 
  Serial.print ("Connecting to");
  Serial.print (WIFI_SSID);
  while (WiFi.status()!= WL_CONNECTED) {
    Serial.print (".");
    delay (500);
  }
  Serial.println ();
  Serial.print ("Connected to");
  Serial.print (" ");
  Serial.println (WIFI_SSID);
  Serial.print ("IP Address is:");
  Serial.println (WiFi.localIP ()); 
  Firebase.begin (FIREBASE_HOST, FIREBASE_AUTH); 
   sensors.begin();
}
 
void loop()
{
   sensors.requestTemperatures();

  Celsius = sensors.getTempCByIndex(0);
  Fahrenheit = sensors.toFahrenheit(Celsius);
   Serial.print(Celsius);
  Serial.print(" C  ");
  String firebaseC = String (Celsius) + String (" C");
  Serial.print(Fahrenheit);
  Serial.println(" F");
  
  String firebaseT = String (Fahrenheit) + String (" F"); 
 
 delay (2000);
 
  
  Firebase.pushString ("Celsius", firebaseC); 
  Firebase.pushString ("Fahrenheit", firebaseT);      
      
}
