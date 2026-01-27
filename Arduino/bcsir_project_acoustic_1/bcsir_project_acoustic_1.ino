// pin definition
int piezoPin = A5;
int ledPin = 9;
int outputV;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);  
}

void loop() {
  // put your main code here, to run repeatedly:
  int sensorValue = analogRead(piezoPin);

  sensorValue = map(sensorValue, 0, 1023, 0, 255);
  outputV = map(sensorValue, 0, 255, 0, 5);

  analogWrite(ledPin, sensorValue);

  // print the results to the Serial Monitor:
  Serial.print("sensor = ");
  Serial.print(piezoPin);
  Serial.print("\t output = ");
  Serial.println(outputV);

}
