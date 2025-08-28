
// constants won't change. Used here to set a pin number:
int ledPin = LED_BUILTIN;  // the number of the LED pin
int pwmPin = 6;
int gndPin = 3;

void setup() {
  // set the digital pin as output:
  pinMode(ledPin, OUTPUT);
  pinMode(pwmPin, OUTPUT);
  pinMode(gndPin, OUTPUT);
  digitalWrite(gndPin, LOW);
}

void loop() {
  // here is where you'd put code that needs to be running all the time.
  
  // digitalWrite(pwmPin, HIGH);
  // delay(10);
  // digitalWrite(pwmPin, LOW);
  // delay(19);
  
  analogWrite(pwmPin, 1);
}
