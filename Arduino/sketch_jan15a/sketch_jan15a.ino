/*
 * This ESP32 code is created by esp32io.com
 *
 * This ESP32 code is released in the public domain
 *
 * For more detail (instruction and wiring diagram), visit https://esp32io.com/tutorials/esp32-automatic-irrigation-system
 */

#define RELAY_PIN    17 // ESP32 pin GPIO17 that connects to relay
#define MOISTURE_PIN 36 // ESP32 pin GPIO36 (ADC0) that connects to AOUT pin of moisture sensor

#define THRESHOLD 1500 // CHANGE YOUR THRESHOLD HERE

void setup() {
  Serial.begin(9600);
  pinMode(RELAY_PIN, OUTPUT);
  // set the ADC attenuation to 11 dB (up to ~3.3V input)
  analogSetAttenuation(ADC_11db);
}

void loop() {
  int value = analogRead(MOISTURE_PIN); // read the analog value from sensor

  if (value > THRESHOLD) {
    Serial.print("The soil is DRY => turn pump ON");
    digitalWrite(RELAY_PIN, HIGH);
  } else {
    Serial.print("The soil is WET => turn pump OFF");
    digitalWrite(RELAY_PIN, LOW);
  }

  Serial.print(" (");
  Serial.print(value);
  Serial.println(")");

  delay(200);
}
