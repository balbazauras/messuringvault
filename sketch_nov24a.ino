#include <HTTPClient.h>
#include <WiFiClient.h>
#include <Wire.h>
#include "WiFi.h"
#include <Bridge.h>

const int trigerPin = 23;
const int echoPin = 22;
const char* ssid     = "ASUS";
const char* password = "apsikase";
const char* serverName = "https://messuringvault.000webhostapp.com/post-esp-data.php";
const String apiKeyValue = "tPmAT5Ab3j7F9";
const String sensor = "HC-SR04";
const String location = "Home";
long duration;
int distance;

void setup() {
  pinMode(echoPin, INPUT);
  pinMode(trigerPin, OUTPUT);
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  digitalWrite(trigerPin, LOW); 
  delayMicroseconds(2);
  digitalWrite(trigerPin, HIGH); 
  delayMicroseconds(10);
  digitalWrite(trigerPin, LOW); 
  int distance = pulseIn(echoPin, HIGH); 
  distance = distance / 58;
  Serial.println(distance);
  if(WiFi.status()== WL_CONNECTED){
    HTTPClient http;
    http.begin(serverName);
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");
    String httpRequestData = "api_key=" + apiKeyValue + "&sensor=" + sensor
                          + "&location=" + location + "&value1=" + String(distance);
    Serial.print("httpRequestData: ");
    Serial.println(httpRequestData);
    
    int httpResponseCode = http.POST(httpRequestData);
    if (httpResponseCode>0) {
      Serial.print("HTTP Response code: ");
      Serial.println(httpResponseCode);
    }
    else {
      Serial.print("Error code: ");
      Serial.println(httpResponseCode);
    }
    http.end();
  }
  else {
    Serial.println("WiFi Disconnected");
  }
  delay(30000);  
}
