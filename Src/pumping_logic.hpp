/* Moisture Sensor Logic Header File
 * Project: Automated Plant Watering System
 * Description: This file contains the setup for logic for reading moisture sensors,
 *              determining soil moisture levels, and controlling the RGB LED
 *              to indicate the moisture status. It also reads the water level
 *              from a dedicated sensor.
 * 
 * Author: John Welgoss
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
const int PIN_SENSOR_4 = 3; // Water-level sensor -> a3

const int RED_PIN = 10;
const int GREEN_PIN = 9;
const int BLUE_PIN = 8; 

// Readings 
const int READING_AIR = 520;
const int READING_WATER = 260;
const int INTERVALS = (READING_AIR - READING_WATER) / 3; 

int MOISTURE_READING_1 = 0;
int MOISTURE_READING_2 = 0;
int MOISTURE_READING_3 = 0;
int WATER_LEVEL = 0;
int AVE_READING = 0;

// Rates 
const int LCD_REFRESH = 500; // Read new data every 0.5s
const int BAUD_RATE = 9600; // Baud rate as 9600 bps 