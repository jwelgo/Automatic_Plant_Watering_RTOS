/** Software-Hardware Test Script for Moisture Sensors
 * @project: Automated Plant Watering System
 * @description: This file contains Tests for reading moisture sensors,
 *               determining soil moisture levels
 */

const int BAUD_RATE = 9600; // Baud rate as 9600 bps 

void setup() {
  Serial.begin(BAUD_RATE); 
  Serial.println("Moisture Sensor Test Started...");
}

void loop() {
  int r1 = analogRead(0);
  int r2 = analogRead(1);
  int r3 = analogRead(2);

  Serial.print("Sensor 1: ");
  Serial.println(r1);
  Serial.print("Sensor 2: ");
  Serial.println(r2);
  Serial.print("Sensor 3: ");
  Serial.println(r3);

  delay(500);
}
