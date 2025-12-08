const int PUMP = 7;

void setup() {
  Serial.begin(9600);
  pinMode(PUMP, OUTPUT);

  digitalWrite(PUMP, HIGH);  
  Serial.println("Pump Motor Test Started...");
}

void loop() {
  Serial.println("Pump ON");
  digitalWrite(PUMP_PIN, LOW);
  delay(2000);

  Serial.println("Pump OFF");
  digitalWrite(PUMP_PIN, HIGH); 
  delay(2000);
}
