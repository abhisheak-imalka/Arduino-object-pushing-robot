#include <Servo.h>

Servo servo; // Create a servo object
const int servoPin = 9; // Pin for servo motor

// Motor control pins
const int LeftMotorForward = 7;
const int LeftMotorBackward = 6;
const int RightMotorForward = 5;
const int RightMotorBackward = 4;

// Ultrasonic sensor pins
#define trig_pin A1 // Trig pin
#define echo_pin A2 // Echo pin

// Variables
long duration;
int distance;

void setup() {
  // Set motor pins as outputs
  pinMode(LeftMotorForward, OUTPUT);
  pinMode(LeftMotorBackward, OUTPUT);
  pinMode(RightMotorForward, OUTPUT);
  pinMode(RightMotorBackward, OUTPUT);

  // Set ultrasonic pins
  pinMode(trig_pin, OUTPUT);
  pinMode(echo_pin, INPUT);

  // Attach servo to pin
  servo.attach(servoPin);

  Serial.begin(9600); // Start serial communication
}

void loop() {
  // Step 1: Rotate the servo motor to scan the environment
  for (int angle = 0; angle <= 180; angle += 30) {
    servo.write(angle); // Rotate servo
    delay(500); // Wait for servo to reach position

    // Step 2: Measure distance using ultrasonic sensor
    distance = measureDistance();
    Serial.print("Angle: ");
    Serial.print(angle);
    Serial.print(" Distance: ");
    Serial.println(distance);

    // Step 3: If an object is detected within a reasonable range (e.g., < 100cm)
    if (distance > 0 && distance < 100) {
      // Move the car in the direction of the object
      moveTowardsObject(angle);
      
      // Stop the car when the distance is 25mm or less
      while (measureDistance() > 2.5) {
        delay(100); // Keep checking the distance
      }
      
      stopCar(); // Stop the car
      delay(5000); // Wait for 5 seconds
      
      break; // Break out of the loop after reaching the object
    }
  }

  // Step 6: Repeat the process
  delay(1000);
}

// Function to measure distance using ultrasonic sensor
int measureDistance() {
  digitalWrite(trig_pin, LOW);
  delayMicroseconds(2);
  digitalWrite(trig_pin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig_pin, LOW);

  duration = pulseIn(echo_pin, HIGH); // Measure the time for echo
  distance = duration * 0.034 / 2; // Calculate the distance in cm
  return distance;
}

// Function to move the car in the direction of the object based on servo angle
void moveTowardsObject(int angle) {
  if (angle < 90) {
    // Object is on the left
    moveLeft();
  } else if (angle > 90) {
    // Object is on the right
    moveRight();
  } else {
    // Object is straight ahead
    moveForward();
  }
}

// Functions to control the motor car
void moveForward() {
  digitalWrite(LeftMotorForward, HIGH);
  digitalWrite(LeftMotorBackward, LOW);
  digitalWrite(RightMotorForward, HIGH);
  digitalWrite(RightMotorBackward, LOW);
  Serial.println("Moving forward");
}

void moveLeft() {
  digitalWrite(LeftMotorForward, LOW);
  digitalWrite(LeftMotorBackward, HIGH);
  digitalWrite(RightMotorForward, HIGH);
  digitalWrite(RightMotorBackward, LOW);
  Serial.println("Turning left");
}

void moveRight() {
  digitalWrite(LeftMotorForward, HIGH);
  digitalWrite(LeftMotorBackward, LOW);
  digitalWrite(RightMotorForward, LOW);
  digitalWrite(RightMotorBackward, HIGH);
  Serial.println("Turning right");
}

void stopCar() {
  digitalWrite(LeftMotorForward, LOW);
  digitalWrite(LeftMotorBackward, LOW);
  digitalWrite(RightMotorForward, LOW);
  digitalWrite(RightMotorBackward, LOW);
  Serial.println("Stopping car");
}
