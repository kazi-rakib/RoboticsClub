/*
 * Project for LSCC Science Fair 2025
 *
 * https://github.com/kazi-rakib/RoboticsClub/Projects/ScienceFair25
 *
 * by Rakib Hasan
 */
#define SERVO_PIN 3
 
#include <Servo.h>

Servo myservo;
int pos = 0;

const int servoPin = SERVO_PIN;
const int trigPin = 9;
const int echoPin = 10;
const int buzzerPin = 13;

int potPin = A0;  // analog pin used to connect the potentiometer
int potValue = 10;    // variable to read the value from the analog pin


long duration, distance;

void setup() {
  myservo.attach(servoPin);
  myservo.write(pos);
  
  pinMode(11, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT); // for LED indicator

  digitalWrite(11, LOW); // optional, for sonar sensor 
  digitalWrite(8, HIGH); // optional, for sonar sensor

  pinMode(buzzerPin, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(9600);
}

void loop() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  distance = (duration*.0343)/2; // in cm
  // distance = (duration*AIR_SPEED)/2; // in cm
  delay(100);

  potValue = analogRead(potPin);            // reads the value of the potentiometer (value between 0 and 1023)
  potValue = map(potValue, 0, 1023, 10, 400);     // scale it for use with the servo (value between 0 and 180)


  if (distance < potValue){
    digitalWrite(13, HIGH); 
    tone(buzzerPin, 4000);
    myservo.write(90);
    
  } else {
    digitalWrite(13, LOW); 
    noTone(buzzerPin);
    myservo.write(0);
  }


  

  /// FOR DEBUGGING
  // /*  
  // convert the time into a distance
  int inches = microsecondsToInches(duration);
  int cm = microsecondsToCentimeters(duration);

  Serial.print("potentiometer: ");
  Serial.println(potValue);

  Serial.print(inches);
  Serial.print("in, ");
  Serial.print(cm);
  Serial.print("cm");
  Serial.println();
  Serial.print(distance);
  Serial.print("cm");
  Serial.println();
  

  delay(100);
  // */
}


long microsecondsToInches(long microseconds) {
  // According to Parallax's datasheet for the PING))), there are 73.746
  // microseconds per inch (i.e. sound travels at 1130 feet per second).
  // This gives the distance travelled by the ping, outbound and return,
  // so we divide by 2 to get the distance of the obstacle.
  // See: https://www.parallax.com/package/ping-ultrasonic-distance-sensor-downloads/
  return microseconds / 74 / 2;
}

long microsecondsToCentimeters(long microseconds) {
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the object we
  // take half of the distance travelled.
  return microseconds / 29 / 2;
}
