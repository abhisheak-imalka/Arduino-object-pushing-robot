void setup() {
  // Initialize serial communication at 9600 bps
  Serial.begin(9600);
  
  // Set pin 4 as input for detection
  pinMode(4, INPUT);

  // Pin 11 and 12 are set as output (presumably for other purposes)

}

void loop() {
  // Check the input on pin 4
  if(digitalRead(4) == LOW){
    Serial.println("No detected");  // Corrected Serial print statement
  }
  else{
    Serial.println("Detected");
  }

  // Add a small delay to prevent flooding the serial output
  delay(500);
}
