/* Moisture Sensor Test Run
 * This code reads data from a moisture sensor connected to analog pin A0
 * and displays the moisture level on a 16x2 LCD screen. It also sends the
 * moisture data to the serial monitor every 20 seconds.
 * 
 * Hardware Connections:
 * - Moisture Sensor: Connect the sensor's output to analog pin A0.
 * - LCD Display: Connect the LCD to digital pins 2, 3, 4, 5, 11, and 12.
 */

// Import necessary packages
#include <LiquidCrystal.h>
#include <Arduino.h>
#include <string.h>

// Define global variables 

// GPIOs
const int PIN_SENSOR_1 = 0; // Moisture sensor 1 -> a0
const int PIN_SENSOR_2 = 1; // Moisture sensor 2 -> a1
const int PIN_SENSOR_3 = 2; // Moisture sensor 3 -> a2

// Readings 
const int READING_AIR = 520;
const int READING_WATER = 260;
const int INTERVALS = (READING_AIR - READING_WATER) / 3; 

int MOISTURE_READING_1 = 0;
int MOISTURE_READING_2 = 0;
int MOISTURE_READING_3 = 0;
int AVE_READING = 0;

// Rates 
const int LCD_REFRESH = 500; // Read new data every 0.5s
const int BAUD_RATE = 9600; // Baud rate as 9600 bps 

// Creates an LCD object. Parameters: (rs, enable, d4, d5, d6, d7)
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

void setup() {
  // LCD setup
  lcd.begin(16, 2); // Set up the LCD's number of columns and rows:
  lcd.clear(); // Clears the LCD screen

  // Moisture sensor setup
  Serial.begin(BAUD_RATE); // Open serial port, set the baud rate
}

void loop() {
  MOISTURE_READING_1 = analogRead(PIN_SENSOR_1);
  MOISTURE_READING_2 = analogRead(PIN_SENSOR_2);
  MOISTURE_READING_3 = analogRead(PIN_SENSOR_3);

  AVE_READING = (MOISTURE_READING_1 + MOISTURE_READING_2 + MOISTURE_READING_3) / 3;

  String val = "NULL Input";
  if (AVE_READING > READING_WATER && AVE_READING < (READING_WATER + INTERVALS)) {
    val = "Very Wet";
  }
  else if (AVE_READING > (READING_WATER + INTERVALS) && AVE_READING < (READING_AIR - INTERVALS)) {
    val = "Wet";
  }
  else if (AVE_READING < READING_AIR && AVE_READING > (READING_AIR - INTERVALS)) {
    val = "Dry";
  }  

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Moisture:");
  lcd.setCursor(0,1);
  lcd.print(val);  

  delay(LCD_REFRESH);  
}
