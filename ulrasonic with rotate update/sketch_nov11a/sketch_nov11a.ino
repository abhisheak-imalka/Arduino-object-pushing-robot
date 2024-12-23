// Define pins for the ultrasonic sensor and motor driver
const int trigPin = 9;
const int echoPin = 10;
const int LeftMotorForward = 7;
const int LeftMotorBackward = 6;
const int RightMotorForward = 5;
const int RightMotorBackward = 4;

// Define distance thresholds (in centimeters)
const int detectionThreshold = 20;  // Distance to detect an object and stop rotating
const int approachThreshold = 5;    // Distance to stop moving forward near the object

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
}

void loop() {
  // Measure distance from object
  long distance = getDistance();

  if (distance < detectionThreshold) {
    // Stop rotating and go toward the object
    stopCar();
    delay(500); // Short pause before moving forward

    // Move forward until close to the object or object is removed
    while (getDistance() > approachThreshold) {
      distance = getDistance();
      if (distance > detectionThreshold) {
        // If the object is removed, break out of the loop to resume rotating
        break;
      }
      moveForward();
      delay(100);  // Small delay for stability
    }

    // Stop moving when close to the object or if object is removed
    stopCar();
    delay(500); // Small pause to stabilize before rechecking

  } else {
    // If no object is detected within the threshold, continue rotating left
    rotateLeft();
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
