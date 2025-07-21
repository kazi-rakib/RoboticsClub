/*
 * Project for LSCC Science Fair 2025
 *
 * https://github.com/kazi-rakib/RoboticsClub/Projects/ScienceFair25
 *
 * by Rakib Hasan
 */
#define RELAY_PIN 3
#define MINIMUM_DISTANCE 10
 
const int servoPin = RELAY_PIN;
const int trigPin = 9;
const int echoPin = 10;
const int buzzerPin = 13;

int potPin = A0;  // analog pin used to connect the potentiometer
int potValue = 10;    // variable to read the value from the analog pin


long duration, distance;

void setup() {
   
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
  potValue = map(potValue, 0, 1023, MINIMUM_DISTANCE, 400);     // scale it for use with the servo (value between 0 and 180)


  if (distance < MINIMUM_DISTANCE){
    digitalWrite(13, HIGH); 
    tone(buzzerPin, 4000);
    digitalWrite(servoPin, HIGH);
    
  } else {
    digitalWrite(13, LOW); 
    noTone(buzzerPin);
    digitalWrite(servoPin, LOW);
  }

}

