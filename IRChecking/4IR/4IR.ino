// Motor control pins
const int LeftMotorForward = 7;
const int LeftMotorBackward = 6;
const int RightMotorForward = 5;
const int RightMotorBackward = 4;

// TCRT5000 sensor pins
const int sensor1Pin = 2;  // First sensor
const int sensor2Pin = 3;  // Second sensor
const int sensor3Pin = 8;  // Third sensor
const int sensor4Pin = 9;  // Fourth sensor

boolean goesForward = false;

void setup() {
  // Initialize serial communication
  Serial.begin(9600);

  // Set sensor pins as input
  pinMode(sensor1Pin, INPUT);
  pinMode(sensor2Pin, INPUT);
  pinMode(sensor3Pin, INPUT);
  pinMode(sensor4Pin, INPUT);

  // Set motor pins as outputs
  pinMode(LeftMotorForward, OUTPUT);
  pinMode(LeftMotorBackward, OUTPUT);
  pinMode(RightMotorForward, OUTPUT);
  pinMode(RightMotorBackward, OUTPUT);

  // Initially move forward
  moveForward();
}

void loop() {
  // Read the sensor values
  int sensor1Value = digitalRead(sensor1Pin);
  int sensor2Value = digitalRead(sensor2Pin);
  int sensor3Value = digitalRead(sensor3Pin);
  int sensor4Value = digitalRead(sensor4Pin);

  // Check if any sensor detects a black color
  if (sensor1Value == LOW && sensor2Value == LOW) {
    Serial.println("Black color detected on one of the sensors, stopping the car");
     // Stop the car when any sensor detects black color
     
     moveForward();
  } else {
    Serial.println("No black color detected, moving forward");
    // Move forward otherwise
    moveStop();
    
  }

  delay(100); // Small delay for stability
}

// Functions to control the motor car
void moveForward() {
  if (!goesForward) {
    goesForward = true;

    digitalWrite(LeftMotorForward, HIGH);
    digitalWrite(RightMotorForward, HIGH);
    digitalWrite(LeftMotorBackward, LOW);
    digitalWrite(RightMotorBackward, LOW);

    Serial.println("Moving forward");
  }
}

void moveStop() {
  goesForward = false;

  digitalWrite(LeftMotorForward, LOW);
  digitalWrite(RightMotorForward, LOW);
  digitalWrite(LeftMotorBackward, LOW);
  digitalWrite(RightMotorBackward, LOW);

  Serial.println("Car stopped");
}
