/*
 * Project for Robotics Club
 *
 * https://github.com/kazi-rakib/RoboticsClub/Arduino/sonar_with_display
 *
 * by Rakib Hasan
 */
#include "myDisplay.h"
#define MINIMUM_DISTANCE 6.0

// SENSOR ====================================================================
const int trigPin = 9;
const int echoPin = 10;
const int buzzerPin = 3;
const int loadPin = 12;

long duration;
float cm, inches;

void setup() {
  Serial.begin(115200); 
  Serial.println(F("Starting!"));

  // DISPLAY ====================================================================
  initializeMyDisplay();
  
  // SENSOR ====================================================================
  pinMode(11, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT); // for LED indicator

  digitalWrite(11, LOW); // optional, for sonar sensor 
  digitalWrite(8, HIGH); // optional, for sonar sensor

  pinMode(buzzerPin, OUTPUT);
  pinMode(loadPin, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  // Serial.begin(9600);
}

void loop() {
  // PING
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  // convert the time into a distance
  inches = microsecondsToInches(duration);
  cm = microsecondsToCentimeters(duration);
  
  // distance = (duration*.0343)/2; // in cm
  // distance = (duration*AIR_SPEED)/2; // in cm
  // delay(100);

  // DISPLAY =====================================================
  myDisplay("Distance", cm, "        cm");

  // Sound the buzzer, turn on the load
  if(cm < MINIMUM_DISTANCE){
    digitalWrite(loadPin, LOW);
    digitalWrite(2, LOW);  
    tone(buzzerPin, 1000, 3000);
    
  }else {
    noTone(buzzerPin);
    digitalWrite(loadPin, HIGH);
    digitalWrite(2, HIGH);
  }

  /// FOR DEBUGGING
  // /*  
  Serial.print(inches);
  Serial.print("in, ");
  Serial.print(cm);
  Serial.print("cm");
  Serial.println();
  // */
  delay(100);  
}

float microsecondsToCentimeters(long microseconds) {
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the object we
  // take half of the distance travelled.
  return (float) microseconds / 29 / 2;
}

float microsecondsToInches(long microseconds) {
  // According to Parallax's datasheet for the PING))), there are 73.746
  // microseconds per inch (i.e. sound travels at 1130 feet per second).
  // This gives the distance travelled by the ping, outbound and return,
  // so we divide by 2 to get the distance of the obstacle.
  // See: https://www.parallax.com/package/ping-ultrasonic-distance-sensor-downloads/
  return (float) microseconds / 74 / 2;
}
