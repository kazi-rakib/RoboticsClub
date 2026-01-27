const int dry = 595; // value for dry sensor
const int wet = 300; // value for wet sensor

int threshold = 40;
int relayPin = 3;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  pinMode(relayPin, OUTPUT); 
}

void loop() {
  // put your main code here, to run repeatedly:
  int sensorVal = analogRead(A0);

  int percentageHumidity = map(sensorVal, wet, dry, 100, 0);

  Serial.print(percentageHumidity);
  Serial.println("%");

  if(percentageHumidity < threshold){
    // turns relay on
    digitalWrite(relayPin, LOW);

  } else {
    // turns relay off
    digitalWrite(relayPin, HIGH);
  }


  delay(1000);
}
