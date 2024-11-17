// Pin Definitions
const int trigPin = 9;
const int echoPin = 10;
const int buzzerPin = 11;
const int ledPin = 13;  // Pin for LED
const int motorPin = 5; // Pin for Vibration Motor

// Constants
const int distanceThreshold = 60; // Distance in cm to trigger buzzer, LED, and motor

// Variables
long duration;
int distance;  // Integer distance value

void setup() {
  // Pin modes
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(ledPin, OUTPUT);  // Set LED pin as output
  pinMode(motorPin, OUTPUT);  // Set motor pin as output

  // Ensure buzzer, LED, and motor are off initially
  digitalWrite(buzzerPin, LOW);
  digitalWrite(ledPin, LOW);
  digitalWrite(motorPin, LOW);

  // Initialize serial for debugging
  Serial.begin(9600);
}

void loop() {
  // Measure distance
  distance = measureDistance();

  // Check distance and activate buzzer, LED, and motor if too close
  if (distance > 0 && distance <= distanceThreshold) {
    // Make the buzzer beep
    beepBuzzer();

    // Turn LED on
    digitalWrite(ledPin, HIGH);

    // Turn motor on
    digitalWrite(motorPin, HIGH);
  } else {
    digitalWrite(buzzerPin, LOW);  // Turn buzzer off
    digitalWrite(ledPin, LOW);     // Turn LED off
    digitalWrite(motorPin, LOW);   // Turn motor off
  }

  // Debugging output
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  // Delay for stability
  delay(100);
}

// Function to measure distance using ultrasonic sensor
int measureDistance() {
  // Trigger a 10µs pulse
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Read echo time
  duration = pulseIn(echoPin, HIGH);

  // Calculate distance (duration * speed of sound / 2)
  int calculatedDistance = (duration * 0.034) / 2;

  // Return distance or a large number if out of range
  if (calculatedDistance >= 400 || calculatedDistance <= 0) {
    return 999; // Out of range
  }
  return calculatedDistance;
}

// Function to make the buzzer beep continuously
void beepBuzzer() {
  // Turn buzzer on
  digitalWrite(buzzerPin, HIGH);
  delay(200);  // Buzzer stays on for 200ms
  digitalWrite(buzzerPin, LOW);
  delay(200);  // Buzzer stays off for 200ms
}
