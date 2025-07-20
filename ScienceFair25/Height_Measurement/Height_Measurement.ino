/*
 * Project for LSCC Science Fair 2025
 *
 * https://github.com/kazi-rakib/RoboticsClub/Projects/ScienceFair25
 *
 * by Rakib Hasan
 */

// DISPLAY ====================================================================
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
 
// 'batman', 32x13px
const unsigned char batman [] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x60, 0x06, 0x00, 0x01, 0xc1, 0x83, 0x80, 0x07, 0xc3, 0xc3, 0xe0,
    0x0f, 0xe3, 0xc7, 0xf0, 0x0f, 0xff, 0xff, 0xf0, 0x1f, 0xff, 0xff, 0xf8, 0x1f, 0xff, 0xff, 0xf8,
    0x0f, 0xff, 0xff, 0xf0, 0x0f, 0x3b, 0xdc, 0xf0, 0x06, 0x01, 0x80, 0x60, 0x03, 0x01, 0x80, 0xc0,
    0x00, 0x00, 0x00, 0x00
};
 
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
 
// ------------------- For i2c -------------------
//// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
 


// SENSOR ====================================================================
const int trigPin = 9;
const int echoPin = 10;
const int buzzerPin = 13;
const int loadPin = 3;

long duration = 3000;
float cm, inches, HEIGHTcm, HEIGHTin;

void setup() {
  // DISPLAY ====================================================================
    Serial.begin(115200);
 
  delay(2000);
  Serial.println(F("Starting!"));
 
  // ------------------- For SPI -------------------
  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
//  if(!display.begin(SSD1306_SWITCHCAPVCC)) {
//    Serial.println(F("SSD1306 allocation failed"));
//    for(;;); // Don't proceed, loop forever
//  }
 
//  ------------------- For i2c -------------------
//  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
  Serial.println(F("Initialized!"));
 
  // Show initial display buffer contents on the screen --
  display.clearDisplay();
  display.drawBitmap(0, 0, batman, 32, 13, WHITE);
 
  display.display();


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
  HEIGHTcm = 180.0 - cm;
  HEIGHTin = 70.866 - inches;

  // distance = (duration*.0343)/2; // in cm
  // distance = (duration*AIR_SPEED)/2; // in cm
  // delay(100);

  // DISPLAY =====================================================
  display.setTextSize(1.5);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.println("ROBOTICS CLUB");
  display.setTextSize(1);
  display.println("Height in, ");
  display.println("    cm: ");
  display.println(HEIGHTcm);
  display.println("    inches: ");
  display.println(HEIGHTin);

  display.println("Thank you!");
  display.display();

  // Sound the buzzer
  if(HEIGHTcm > 0){
    tone(buzzerPin, 1000, 3000);
  }else {
    noTone(buzzerPin);
  }

  delay(20000); // let the visitors see his/her own height for 20 seconds
  display.clearDisplay();

  

  /// FOR DEBUGGING
  // /*  
  Serial.print(HEIGHTin);
  Serial.print("in, ");
  Serial.print(HEIGHTcm);
  Serial.print("cm");
  Serial.println();
  // */
  delay(100);
  
}


float microsecondsToInches(long microseconds) {
  // According to Parallax's datasheet for the PING))), there are 73.746
  // microseconds per inch (i.e. sound travels at 1130 feet per second).
  // This gives the distance travelled by the ping, outbound and return,
  // so we divide by 2 to get the distance of the obstacle.
  // See: https://www.parallax.com/package/ping-ultrasonic-distance-sensor-downloads/
  return (float) microseconds / 74 / 2;
}

float microsecondsToCentimeters(long microseconds) {
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the object we
  // take half of the distance travelled.
  return (float) microseconds / 29 / 2;
}

