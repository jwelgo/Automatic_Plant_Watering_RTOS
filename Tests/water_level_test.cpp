/** Software/Hardware Test Script for Water Level Sensor
 * @project: Automated Plant Watering System
 * @description: This file contains tests for the water level sensor
 */

const int TO_MM = 13;

void setup() {
  Serial.begin(9600);
  Serial.println("Water Level Sensor Test Started...");
}

void loop() {
  int reading = analogRead(3);
  int waterLevel = reading / TO_MM;

  Serial.print("Reading: ");
  Serial.println(reading);
  Serial.print("Level: ");
  Serial.println(waterLevel);

  delay(500);
}
