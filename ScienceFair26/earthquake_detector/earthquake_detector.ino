// Earthquake Detector with ADXL345 Accelerometer
// This code detects vibrations and logs earthquake-like events

#include <Wire.h>
#include <Adafruit_ADXL345_U.h>

// Create accelerometer object
Adafruit_ADXL345_Unified accel = Adafruit_ADXL345_Unified(12345);

// Pin definitions
const int buzzerPin = 8;
const int ledPinGreen = 9;   // Normal/safe
const int ledPinYellow = 10; // Minor shaking
const int ledPinRed = 11;    // Strong shaking

// Threshold values (adjust based on testing)
const float minorThreshold = 0.5;   // m/s² above baseline
const float strongThreshold = 1.5;  // m/s² above baseline

// Variables for baseline and detection
float baselineX = 0, baselineY = 0, baselineZ = 0;
bool isCalibrated = false;
unsigned long eventStartTime = 0;
bool eventActive = false;

void setup() {
  Serial.begin(9600);
  
  // Initialize pins
  pinMode(buzzerPin, OUTPUT);
  pinMode(ledPinGreen, OUTPUT);
  pinMode(ledPinYellow, OUTPUT);
  pinMode(ledPinRed, OUTPUT);
  
  // Initialize accelerometer
  if(!accel.begin()) {
    Serial.println("No ADXL345 detected. Check wiring!");
    while(1);
  }
  
  // Set range to +/- 16g for better earthquake detection
  accel.setRange(ADXL345_RANGE_16_G);
  
  Serial.println("Earthquake Detector Initialized");
  Serial.println("Calibrating... Keep sensor still for 3 seconds");
  
  // Calibrate baseline
  calibrateBaseline();
  
  Serial.println("Calibration complete!");
  Serial.println("Monitoring for vibrations...");
  Serial.println("Time(ms), X(m/s²), Y(m/s²), Z(m/s²), Magnitude, Status");
  
  digitalWrite(ledPinGreen, HIGH);
}

void loop() {
  // Get sensor event
  sensors_event_t event;
  accel.getEvent(&event);
  
  // Calculate deviation from baseline
  float deltaX = abs(event.acceleration.x - baselineX);
  float deltaY = abs(event.acceleration.y - baselineY);
  float deltaZ = abs(event.acceleration.z - baselineZ);
  
  // Calculate magnitude of vibration
  float magnitude = sqrt(deltaX*deltaX + deltaY*deltaY + deltaZ*deltaZ);
  
  // Log data to Serial (for plotting and analysis)
  Serial.print(millis());
  Serial.print(",");
  Serial.print(event.acceleration.x, 3);
  Serial.print(",");
  Serial.print(event.acceleration.y, 3);
  Serial.print(",");
  Serial.print(event.acceleration.z, 3);
  Serial.print(",");
  Serial.print(magnitude, 3);
  Serial.print(",");
  
  // Determine alert level and respond
  if (magnitude > strongThreshold) {
    // Strong shaking detected
    digitalWrite(ledPinGreen, LOW);
    digitalWrite(ledPinYellow, LOW);
    digitalWrite(ledPinRed, HIGH);
    tone(buzzerPin, 2000, 200); // High pitched alarm
    Serial.println("STRONG");
    
    if (!eventActive) {
      eventStartTime = millis();
      eventActive = true;
    }
    
  } else if (magnitude > minorThreshold) {
    // Minor shaking detected
    digitalWrite(ledPinGreen, LOW);
    digitalWrite(ledPinYellow, HIGH);
    digitalWrite(ledPinRed, LOW);
    tone(buzzerPin, 1000, 100); // Medium pitched alert
    Serial.println("MINOR");
    
    if (!eventActive) {
      eventStartTime = millis();
      eventActive = true;
    }
    
  } else {
    // Normal - no significant shaking
    digitalWrite(ledPinGreen, HIGH);
    digitalWrite(ledPinYellow, LOW);
    digitalWrite(ledPinRed, LOW);
    noTone(buzzerPin);
    Serial.println("NORMAL");
    
    // If event was active, log duration
    if (eventActive) {
      unsigned long duration = millis() - eventStartTime;
      Serial.print("EVENT ENDED - Duration: ");
      Serial.print(duration);
      Serial.println(" ms");
      eventActive = false;
    }
  }
  
  delay(100); // Sample 10 times per second
}

void calibrateBaseline() {
  int samples = 30;
  float sumX = 0, sumY = 0, sumZ = 0;
  
  for(int i = 0; i < samples; i++) {
    sensors_event_t event;
    accel.getEvent(&event);
    
    sumX += event.acceleration.x;
    sumY += event.acceleration.y;
    sumZ += event.acceleration.z;
    
    delay(100);
  }
  
  baselineX = sumX / samples;
  baselineY = sumY / samples;
  baselineZ = sumZ / samples;
  
  Serial.print("Baseline: X=");
  Serial.print(baselineX);
  Serial.print(" Y=");
  Serial.print(baselineY);
  Serial.print(" Z=");
  Serial.println(baselineZ);
}