/** Moisture Sensor Logic File
 * @project: Automated Plant Watering System
 * @description: This file contains the logic for reading moisture sensors,
 *               determining soil moisture levels, and controlling the RGB LED
 *               to indicate the moisture status. It also reads the water level
 *               from a dedicated sensor.
 */


// Import necessary packages
#include <LiquidCrystal.h>
#include <Arduino.h>
#include <string.h>
#include <stdint.h>
// Include pumping logic

// Define global variables 
// LCD
LiquidCrystal lcd(12, 11, 10, 9, 8, 4);  

//Buttons 
const uint8_t BUTTON_MODE = 4; // Mode Button -> a4
const uint8_t BUTTON_START = 5; // Mode Button -> a5

// GPIOs
const uint8_t PIN_SENSOR_1 = 0; // Moisture sensor 1 -> a0
const uint8_t PIN_SENSOR_2 = 1; // Moisture sensor 2 -> a1
const uint8_t PIN_SENSOR_3 = 2; // Moisture sensor 3 -> a2
const uint8_t PIN_SENSOR_4 = 3; // Water-level sensor -> a3

const uint8_t RED_PIN = 3;
const uint8_t GREEN_PIN = 5;
const uint8_t BLUE_PIN = 6; 
const uint8_t WARNING_PIN = 2;
const uint8_t PUMP_PIN = 7;

// Readings and Constants 
const uint16_t READING_AIR = 520;
const uint16_t READING_WATER = 260;
const uint16_t INTERVALS = (READING_AIR - READING_WATER) / 3; 
const uint16_t TO_MM = 13;  // Divide Water-Level reading by this to display mm of water

uint16_t MOISTURE_READING_1 = 0;
uint16_t MOISTURE_READING_2 = 0;
uint16_t MOISTURE_READING_3 = 0;
uint16_t WATER_LEVEL = 0;

// Globals
uint8_t sensorMode = 1;      // 1, 2, or 3 sensors
bool systemStarted = false;
unsigned long pumpStartTime = 0;
bool pumpRunning = false;
const unsigned long pumpOnTime = 2000;     
const unsigned long pumpRestTime = 8000; 
unsigned long pumpCycleStart = 0;

// Rates 
const int BAUD_RATE = 9600; // Baud rate as 9600 bps 

// Prototypes 
int readMoisture();
void setColor(int redValue, int greenValue,  int blueValue);
void showStartupMenu();


void setup() {
  Serial.begin(BAUD_RATE); // Open serial port, set the baud rate
  
  // Buttons
  pinMode(BUTTON_MODE, INPUT_PULLUP);
  pinMode(BUTTON_START, INPUT_PULLUP);

  // Outputs
  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);

  pinMode(WARNING_PIN, OUTPUT);
  digitalWrite(WARNING_PIN, LOW);

  pinMode(PUMP_PIN, OUTPUT);
  digitalWrite(PUMP_PIN, HIGH);  // Pump off

  showStartupMenu();  // LCD startup menu
}

void loop() {
  if (!systemStarted)
    return;

  int average = readMoisture();
  int waterLevel = analogRead(PIN_SENSOR_4);

  // Moisture color
  if (average <= READING_WATER + INTERVALS) {
      setColor(0, 64, 255);  // Very Wet (blue)
  }
  else if (average <= READING_WATER + INTERVALS*2) {
      setColor(0, 200, 0);  // Wet (green)
  }
  else {
      setColor(255, 0, 0);   // Dry (red)

      // Start pump if water tank OK
      if (!pumpRunning && waterLevel / TO_MM >= 10) {
          pumpRunning = true;
          pumpStartTime = millis();
          digitalWrite(PUMP_PIN, LOW);
      }
  }

  // Pump timing logic
  if (pumpRunning) {
      unsigned long elapsed = millis() - pumpStartTime;

      if (elapsed >= pumpOnTime && elapsed < pumpOnTime + pumpRestTime) {
          digitalWrite(PUMP_PIN, HIGH);
      }

      if (elapsed >= pumpOnTime + pumpRestTime) {
          pumpRunning = false;
      }
  }

  // Low water warning
  if (waterLevel / TO_MM < 10) {
      digitalWrite(WARNING_PIN, HIGH);
      digitalWrite(PUMP_PIN, HIGH);  // Force pump off
      pumpRunning = false;
  } else {
      digitalWrite(WARNING_PIN, LOW);
  }
}

// Helper Functions
int readMoisture() {
  int r1 = analogRead(PIN_SENSOR_1);
  int r2 = analogRead(PIN_SENSOR_2);
  int r3 = analogRead(PIN_SENSOR_3);

  if (sensorMode == 1)
      return r1;
  if (sensorMode == 2)
      return (r1 + r2) / 2;
  return (r1 + r2 + r3) / 3;
}

void setColor(int redValue, int greenValue,  int blueValue) {
  analogWrite(RED_PIN, redValue);
  analogWrite(GREEN_PIN, greenValue);
  analogWrite(BLUE_PIN, blueValue);
}

// ---------------- STARTUP MENU ----------------

void showStartupMenu() {
  lcd.begin(16, 2);
  lcd.clear();
  lcd.print("Select Sensors");

  while (true) {
      // First line shows mode
      lcd.setCursor(0, 1);
      lcd.print("Mode: ");
      lcd.print(sensorMode);
      lcd.print(" sensor  ");

      // Button MODE cycles through 1 → 2 → 3 → 1
      if (digitalRead(BUTTON_MODE) == LOW) {
          sensorMode++;
          if (sensorMode > 3) sensorMode = 1;
          delay(300);
      }

      // START button locks selection
      if (digitalRead(BUTTON_START) == LOW) {
          delay(250);
          break;
      }
  }

  // Show confirmation
  lcd.clear();
  lcd.print("Starting with");
  lcd.setCursor(0, 1);
  lcd.print(sensorMode);
  lcd.print(" sensors...");
  delay(1000);

  lcd.noDisplay();
  systemStarted = true;
}
