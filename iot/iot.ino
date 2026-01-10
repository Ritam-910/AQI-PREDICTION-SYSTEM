#include <math.h>

// Pins
const int dustPin = A0;
const int mq7Pin = A1;
const int mq135Pin = A2;
const int dustLed = 7;

// Calibration Constants
float dustOffset = 0.065; 
const float RLOAD = 10.0; 
const float R0 = 35.0; // Adjust this after 24h burn-in

void setup() {
  Serial.begin(9600);
  pinMode(dustLed, OUTPUT);
  digitalWrite(dustLed, HIGH); // LED Off
  Serial.println("System Warming Up... (Allow 2 mins)");
}

void loop() {
  // --- PM2.5 (Dust) ---
  digitalWrite(dustLed, LOW);
  delayMicroseconds(280);
  float dustV = analogRead(dustPin) * (5.0 / 1024.0);
  delayMicroseconds(40);
  digitalWrite(dustLed, HIGH);
  float pm25ppm = ((dustV - dustOffset) * 200.0) / 1225.0;
  if (pm25ppm < 0) pm25ppm = 0;

  // --- MQ-7 (CO) ---
  float coV = analogRead(mq7Pin) * (5.0 / 1024.0);
  float coPPM = (coV - 0.15) * 100.0; // Basic estimate
  if (coPPM < 0) coPPM = 0;

  // --- MQ-135 (NH3 & NO2) ---
  float mq135V = analogRead(mq135Pin) * (5.0 / 1024.0);
  float rs = ((5.0 * RLOAD) / mq135V) - RLOAD;
  float ratio = rs / R0;

  // Power Law Formulas from Datasheet
  float ppmNH3 = 102.2 * pow(ratio, -2.47);
  float ppmNO2 = 44.2 * pow(ratio, -2.89);

  // --- Output ---
  Serial.print("D-PPM: "); Serial.print(pm25ppm, 4);
  Serial.print(" | CO: "); Serial.print(coPPM, 1);
  Serial.print(" | NH3: "); Serial.print(ppmNH3, 2);
  Serial.print(" | NO2: "); Serial.println(ppmNO2, 2);

  delay(3000); 
}