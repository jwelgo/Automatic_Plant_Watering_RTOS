# Automatic Plant Watering System  
* A Smart Irrigation Controller with Moisture Sensors, RGB Status LED, Pump Control & Component Safety Features *



## Overview  
This project implements an automated watering system using an Arduino UNO R3.  
It reads soil moisture levels from **1–3 sensors**, controls a **pump**, checks the **resevoir level**, and provides **visual feedback** using RGB LEDs and indicator LEDs.

A startup menu allows the user to select how many moisture sensors to average before the system begins operating. For small plants, a single sensor is used to monitor soil moisture. For larger plants, up to three soil moisture sensors can be activated to read the average soil moisture level around the pot. 

The system is designed for reliability and safety:  
- Pump runs only when soil is dry  
- Pump automatically rests between cycles  
- Low water level shuts off the pump and activates a warning LED (Dry firing the pump can damge the component) 



## Features  

### Moisture Monitoring  
- Up to **3 soil moisture sensors** (A0–A2)  
- Modes: 1-sensor, 2-sensor average, or 3-sensor average  
- Manual selection at startup  

### Visual Feedback  
- **RGB LED** indicates moisture state:  
  - **Blue:** Very wet  
  - **Green:** Wet  
  - **Red:** Dry  
- **Warning LED** lights up **Red** when the water tank is low  
- **SMALL / MEDIUM / LARGE LEDs** show selected mode in the setup menu

### Pump Automation  
- Pump activates if and only if:  
  - Soil is dry  
  - Water level is above 10 mm  
- Pump runs for **2 seconds**, then rests for **8 seconds**.
- The Water supplied by the pump will take a few seconds to settle into the soil, so an **8 second** delay will allow the moisture sensors to wait for a more accurate reading. 
- Low water automatically disables the pump for component safety. 

### Calibration  
Moisture readings use two calibration constants:  
- `READING_AIR = 520`
   - The moisture sensor will read **520** when sitting idle in open air
- `READING_WATER = 260`
   - The moisture sensor will read **260** when sitting idle supmergered in water.
These define three moisture ranges (very wet, wet, dry).
- Dry: **520 - 433.33**
- Wet: **433.33 - 346.66**
- Very Wet: **346.66 - 260**

Water level is converted into millimeters using:  
- `TO_MM = 13`
   - The water level sensore outputs a value from **520 - 0**
   - Dividing this value by 13 converts the reading into millimeters
   - `NOTE:` The usage of millimeters in prefered over milliliters since the purpose of reading the water level is to protect the pump. The pump can sit comfortably at the bottom of the resevoir with about 10 mm of vertical space, so this is the value the sensor is used to monitor.



## Hardware Requirements  
- **Arduino Uno R3**  
- **3 Capacitive Soil Moisture Sensors**
- **Water-level sensor (conductive)** 
- **RGB LED** (Pins 3, 5, 6)  
- **Red Warning LED** (Pin 2)  
- **3 White Mode Indicator LEDs** (Pins 10, 11, 12)  
- **2 Buttons:**  
  - Mode Select (Pin 8)  
  - Start (Pin 9)  
- **Pump + 5V Relay** (Controlled on Pin 7)  
- Wires, resistors (200 - 500 Ohms), 5V power source  



## Pinout Summary  

`Component             Pin`
*******************************
 Button – Mode        | 8   
 Button – Start       | 9   
 LED – Small Mode     | 12  
 LED – Medium Mode    | 11  
 LED – Large Mode     | 10  
 Moisture Sensor 1    | 0 (a0) 
 Moisture Sensor 2    | 1 (a1) 
 Moisture Sensor 3    | 2 (a2) 
 Water-Level Sensor   | 3 (a3) 
 RGB LED – Red        | 3   
 RGB LED – Green      | 5   
 RGB LED – Blue       | 6   
 Warning LED          | 2   
 5V Relay             | 7   



## Using the Pump

### **1. Startup Menu**  
On power-up:  
- Press **MODE** to cycle between:  
  - 1 sensor  
  - 2 sensors  
  - 3 sensors  
- LEDs indicate which mode is active  (Small, Medium, Large Plant Size)
- Press **START** to lock in and begin system operation
- **IMPORTANT**: Make sure resevior is filled and pump nossel is in plant bed before starting

### **2. Normal Operation**  
The system continuously:  
1. Reads moisture sensor(s)  
2. Computes an average based on selected mode  
3. Sets RGB LED to indicate moisture level  
4. Reads water tank level  
5. Controls pump based on moisture and water availability  

### **3. Pump Control Logic**  
- Runs pump for **2 seconds**  
- Rest for **8 seconds**  
- After full 10-second cycle, system resets pump logic  

### **4. Safety Behavior**  
When water level < 10 mm:  
- Pump is immediately turned off  
- Warning LED turns on  
- Pump will not restart until tank is refilled (Device does not have to be reset)



## License  
Free to modify and use for personal or educational purposes (Open Source).
