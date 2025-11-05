#define sensorPwr 7
#define sensorPin A0

int value = 0;

enum potSize {
  MONITORING,
  PUMPING, 
}

unsigned long previousMillis = 0;
int sensorCount = 1;

void setup() {    

  // here we will wait for user input to determine the amount of sensors
  Serial.println("Waiting for sensor count");
  // add possible timeout in case no input is made default to 1 sensor

  int desired = 400; //arbituary default moisture value target

  Serial.println("Setup complete");

}
void loop() {
  unsigned long currentMillis = millis();

  switch(size) {

  }

}

/*
520 is the maximum value of the sensor and the detector is 40mm 
dividing the value by 520/40 gives us the value in mm
520/40 = 13
this will need to be changed when we calibrate
*/

int waterHeight(int input) {

  int ret = (input/13);
  return ret;

}

void setState(potSize newState) {

  // prep for loop

  // switch 
  switch(newState) {
    case MONITORING:
    case PUMPING:
  }

}