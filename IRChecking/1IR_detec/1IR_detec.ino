void setup() {
  // Initialize pin 2 and pin 11 as output
  pinMode(2, OUTPUT);
  pinMode(13, OUTPUT);
}

void loop() {
  // Turn on the LED connected to pin 2
  digitalWrite(2, HIGH);

  // Turn on the LED connected to pin 11
  digitalWrite(13, HIGH);

  // You can add a delay if needed
  // delay(1000); // Wait for 1 second
}
