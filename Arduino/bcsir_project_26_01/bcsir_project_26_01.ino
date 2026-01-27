int mq2Pin = A0; // Analog pin for MQ2
int buzzerPin = 11; // Digital pin for buzzer
int threshold = 400; // Set sensitivity threshold

void setup() {
  pinMode(buzzerPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  int sensorValue = analogRead(mq2Pin);
  Serial.print("Gas Level: ");
  Serial.println(sensorValue);
  
  if (sensorValue > threshold) {
    digitalWrite(buzzerPin, HIGH); // Alarm on
  } else {
    digitalWrite(buzzerPin, LOW); // Alarm off
  }
  delay(500);
}
