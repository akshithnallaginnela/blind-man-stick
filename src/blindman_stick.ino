#include <DHT.h>  // Adafruit DHT sensor library

#define DHTPIN 7         // DHT sensor data pin
#define DHTTYPE DHT22    // DHT22 sensor type

DHT dht(DHTPIN, DHTTYPE);

const int vibrationPin = 6;
const int buzzerPin = 8;  // NEW: Buzzer connected to pin 8

const int trigPinFront = 2;
const int echoPinFront = 3;
const int trigPinBottom = 4;
const int echoPinBottom = 5;

const int vibrationDuration = 100;  // Duration in milliseconds

void setup() {
  Serial.begin(9600);
  Serial.println("Blind Man Stick Initialized");

  // Set pin modes for ultrasonic sensors
  pinMode(trigPinFront, OUTPUT);
  pinMode(echoPinFront, INPUT);
  pinMode(trigPinBottom, OUTPUT);
  pinMode(echoPinBottom, INPUT);

  // Set pin modes for vibration and buzzer
  pinMode(vibrationPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);  // NEW: Buzzer pin as output

  // Initialize DHT sensor
  dht.begin();
}

void loop() {
  // Read humidity
  float h = dht.readHumidity();

  // Measure distances
  long durationFront = measureDistance(trigPinFront, echoPinFront);
  long distanceFront = calculateDistance(durationFront);

  long durationBottom = measureDistance(trigPinBottom, echoPinBottom);
  long distanceBottom = calculateDistance(durationBottom);

  Serial.print("Front Distance: ");
  Serial.print(distanceFront);
  Serial.println(" cm");

  Serial.print("Bottom Distance: ");
  Serial.print(distanceBottom);
  Serial.println(" cm");

  Serial.print("Humidity: ");
  Serial.print(h);
  Serial.println(" %");

  bool obstacleDetected = distanceFront < 5 || distanceBottom < 3;
  bool highHumidity = h > 90;

  if (obstacleDetected || highHumidity) {
    if (obstacleDetected) {
      if (distanceFront < 5) {
        Serial.println("Obstacle detected ahead!");
        triggerAlert(vibrationDuration);  // Vibrate and buzz
        }
      
      if (distanceBottom < 3 ) {
        Serial.println("Obstacle detected below!");
        triggerAlert(vibrationDuration);  // Vibrate and buzz
      }
    }

    if (highHumidity) {
      Serial.println("High humidity detected!");
    }

    triggerAlert(vibrationDuration);  // Vibrate and buzz
  } else {
    // Turn off outputs when conditions are safe
    digitalWrite(vibrationPin, LOW);
    digitalWrite(buzzerPin, LOW);
    delay(500);
  }

  if (isnan(h)) {
    Serial.println("Failed to read from DHT sensor!");
  }

  delay(1000);
}

// Function to measure distance using an ultrasonic sensor
long measureDistance(int trigPin, int echoPin) {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  return pulseIn(echoPin, HIGH);
}

// Function to calculate distance from duration
long calculateDistance(long duration) {
  return duration * 0.0343 / 2;
}

// Function to trigger vibration and buzzer
void triggerAlert(int duration) {
  digitalWrite(vibrationPin, HIGH);
  digitalWrite(buzzerPin, HIGH);  // Turn on buzzer
  delay(duration);
  digitalWrite(vibrationPin, LOW);
  digitalWrite(buzzerPin, LOW);   // Turn off buzzer
}
