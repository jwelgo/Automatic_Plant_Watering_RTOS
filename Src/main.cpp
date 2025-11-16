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

// GPIOs
const uint8_t PIN_SENSOR_1 = 0; // Moisture sensor 1 -> a0
const uint8_t PIN_SENSOR_2 = 1; // Moisture sensor 2 -> a1
const uint8_t PIN_SENSOR_3 = 2; // Moisture sensor 3 -> a2
const uint8_t PIN_SENSOR_4 = 3; // Water-level sensor -> a3

const uint8_t RED_PIN = 10;
const uint8_t GREEN_PIN = 9;
const uint8_t BLUE_PIN = 8; 

// Readings 
const uint16_t READING_AIR = 520;
const uint16_t READING_WATER = 260;
const uint16_t INTERVALS = (READING_AIR - READING_WATER) / 3; 

uin16_t MOISTURE_READING_1 = 0;
uin16_t MOISTURE_READING_2 = 0;
uin16_t MOISTURE_READING_3 = 0;
uin16_t WATER_LEVEL = 0;
uin16_t AVE_READING = 0;

// Rates 
const int LCD_REFRESH = 500; // Read new data every 0.5s
const int BAUD_RATE = 9600; // Baud rate as 9600 bps 

// Creates an LCD object. Parameters: (rs, enable, d4, d5, d6, d7)
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup() {
  // LCD setup
  lcd.begin(16, 2); // Set up the LCD's number of columns and rows:
  lcd.clear(); // Clears the LCD screen
  
  //RGB Setup
  pinMode(RED_PIN,  OUTPUT);              
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);

  // Read initial water-level
  WATER_LEVEL = analogRead(PIN_SENSOR_4);
  
  // Moisture sensor setup
  Serial.begin(BAUD_RATE); // Open serial port, set the baud rate
}

void loop() {
  MOISTURE_READING_1 = analogRead(PIN_SENSOR_1);
  MOISTURE_READING_2 = analogRead(PIN_SENSOR_2);
  MOISTURE_READING_3 = analogRead(PIN_SENSOR_3);

  AVE_READING = (MOISTURE_READING_1 + MOISTURE_READING_2 + MOISTURE_READING_3) / 3;

  if (AVE_READING > READING_WATER && AVE_READING < (READING_WATER + INTERVALS)) {
    setColor(0, 64, 255); // Very wet -> Blue
  }
  else if (AVE_READING > (READING_WATER + INTERVALS) && AVE_READING < (READING_AIR - INTERVALS)) {
    setColor(0, 200, 0); // Wet -> Green
  }
  else if (AVE_READING < READING_AIR && AVE_READING > (READING_AIR - INTERVALS)) {
    setColor(255, 0, 0); // Dry -> Red
    // Pump logic call here
  }

  WATER_LEVEL = analogRead(PIN_SENSOR_4);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Water Level:");
  lcd.setCursor(0,1);
  lcd.print(WATER_LEVEL);  

  delay(LCD_REFRESH); 
}

// Helper function to set RGB color
void setColor(int redValue, int greenValue,  int blueValue) {
  analogWrite(RED_PIN, redValue);
  analogWrite(GREEN_PIN,  greenValue);
  analogWrite(BLUE_PIN, blueValue);
}
