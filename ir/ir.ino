int irSensor = 2; // IR sensor connected to pin 2
int led = 13;     // LED connected to pin 13

void setup() {
  pinMode(irSensor, INPUT);
  pinMode(led, OUTPUT);
}

void loop() {
  int sensorValue = digitalRead(irSensor);
  
  if (sensorValue == HIGH) {
    digitalWrite(led, HIGH); // Turn on the LED
  } else {
    digitalWrite(led, LOW);  // Turn off the LED
  }
}
