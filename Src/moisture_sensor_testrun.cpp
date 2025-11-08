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

// Define global variables 
int MOISTURE_DATA = 0; // Moisture sensor -> a0
int READING_PERIOD = 20000; // Read new data every 2s
int BAUD_RATE = 9600; // Baud rate as 9600 bps 

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
  int val;
  val = analogRead(MOISTURE_DATA); // Connect sensor to Analog 0
  
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Moisture:");
  lcd.setCursor(0,1);
  lcd.print(val);  

  Serial.println(val);

  delay(READING_PERIOD); 
}
