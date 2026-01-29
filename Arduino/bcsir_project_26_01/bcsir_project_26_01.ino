int mq2Pin = A0; // Analog pin for MQ2
int fanPin = 9; // Digital pin for buzzer
int threshold = 400; // Set sensitivity threshold

void setup() {
  pinMode(fanPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  int sensorValue = analogRead(mq2Pin);
  Serial.print("Gas Level: ");
  Serial.println(sensorValue);
  
  if (sensorValue > threshold) {
    digitalWrite(fanPin, HIGH); // Alarm on
  } else {
    digitalWrite(fanPin, LOW); // Alarm off
  }
  delay(500);
}
