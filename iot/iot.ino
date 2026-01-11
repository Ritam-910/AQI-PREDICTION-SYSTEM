#include <WiFi.h>
#include <HTTPClient.h>
#include <math.h>

// --- Pin Mapping for ESP32 ADC1 (Safe for WiFi) ---
const int dustPin = 34;   // Was A0
const int mq7Pin = 35;    // Was A1
const int mq135Pin = 32;  // Was A2
const int dustLed = 27;   // Was Digital 7

// --- Calibration Constants (Matches your Arduino Example) ---
float dustOffset = 0.065; 
const float RLOAD = 10.0; 
const float R0 = 35.0; 

// --- WiFi & Server Config ---
const char* ssid = "YOUR_WIFI_NAME";
const char* password = "YOUR_WIFI_PASSWORD";
const char* serverURL = "http://192.168.1.100:8000/sensor-data"; 

void setup() {
  Serial.begin(115200); // Standard ESP32 Speed
  pinMode(dustLed, OUTPUT);
  digitalWrite(dustLed, HIGH); // LED Off initially

  WiFi.begin(ssid, password);
  Serial.print("Connecting WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi Connected!");
}

void loop() {
  // --- PM2.5 Calculation (Updated for 3.3V / 4095) ---
  digitalWrite(dustLed, LOW);
  delayMicroseconds(280);
  // ESP32 uses 12-bit resolution (0-4095)
  float dustV = analogRead(dustPin) * (3.3 / 4095.0); 
  delayMicroseconds(40);
  digitalWrite(dustLed, HIGH);
  
  float pm25 = ((dustV - dustOffset) * 200.0) / 1225.0;
  if (pm25 < 0) pm25 = 0;

  // --- MQ-7 (CO) Calculation ---
  float coV = analogRead(mq7Pin) * (3.3 / 4095.0);
  float coPPM = (coV - 0.15) * 100.0; 
  if (coPPM < 0) coPPM = 0;

  // --- MQ-135 (NH3 & NO2) Calculation ---
  float mq135V = analogRead(mq135Pin) * (3.3 / 4095.0);
  if (mq135V < 0.1) mq135V = 0.1; // Prevent division by zero
  
  float rs = ((3.3 * RLOAD) / mq135V) - RLOAD;
  float ratio = rs / R0;

  float nh3 = 102.2 * pow(ratio, -2.47);
  float no2 = 44.2 * pow(ratio, -2.89);

  // --- Generate JSON Payload ---
  String jsonPayload = "{";
  jsonPayload += "\"pm25\":" + String(pm25, 4) + ",";
  jsonPayload += "\"co\":" + String(coPPM, 2) + ",";
  jsonPayload += "\"nh3\":" + String(nh3, 2) + ",";
  jsonPayload += "\"no2\":" + String(no2, 2);
  jsonPayload += "}";

  // Print JSON to Serial for monitoring
  Serial.println(jsonPayload);

  // --- Send to MERN Backend via HTTP POST ---
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;
    http.begin(serverURL);
    http.addHeader("Content-Type", "application/json");

    int httpResponseCode = http.POST(jsonPayload);
    
    Serial.print("HTTP Status: ");
    Serial.println(httpResponseCode);
    
    http.end();
  }

  delay(5000); // 5-second interval
}
