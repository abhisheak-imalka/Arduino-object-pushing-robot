// Define pins for the ultrasonic sensor and motor driver
const int trigPin = 9;
const int echoPin = 10;
const int LeftMotorForward = 7;
const int LeftMotorBackward = 6;
const int RightMotorForward = 5;
const int RightMotorBackward = 4;

void setup() {
  Serial.begin(9600);

  // Ultrasonic sensor pin setup
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // Motor driver pin setup
  pinMode(LeftMotorForward, OUTPUT);
  pinMode(LeftMotorBackward, OUTPUT);
  pinMode(RightMotorForward, OUTPUT);
  pinMode(RightMotorBackward, OUTPUT);

  // Start rotating left
  rotateLeft();
}

void loop() {
  // Measure distance from object
  long distance = getDistance();

  // If an object is detected within 20 cm, stop rotating and go toward it
  if (distance < 20) {
    stopCar();  // Stop rotating
    delay(500); // Short pause before moving forward

    // Move forward toward the object until within a close distance (e.g., 5 cm)
    while (getDistance() > 5) {
      moveForward();
      delay(100);  // Small delay for stability
    }

    // Stop when close to the object
    stopCar();
  }
}

// Function to measure distance with ultrasonic sensor
long getDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH);
  long distance = (duration * 0.034) / 2;

  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  return distance;
}

// Function to rotate the car to the left
void rotateLeft() {
  digitalWrite(LeftMotorForward, LOW);
  digitalWrite(LeftMotorBackward, HIGH);
  digitalWrite(RightMotorForward, HIGH);
  digitalWrite(RightMotorBackward, LOW);
}

// Function to move the car forward
void moveForward() {
  digitalWrite(LeftMotorForward, HIGH);
  digitalWrite(LeftMotorBackward, LOW);
  digitalWrite(RightMotorForward, HIGH);
  digitalWrite(RightMotorBackward, LOW);
}

// Function to stop the car
void stopCar() {
  digitalWrite(LeftMotorForward, LOW);
  digitalWrite(LeftMotorBackward, LOW);
  digitalWrite(RightMotorForward, LOW);
  digitalWrite(RightMotorBackward, LOW);
}
