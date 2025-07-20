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
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
 
// ------------------- For SPI -------------------
// Declaration for SSD1306 display connected using software SPI (default case):
//#define OLED_MOSI   D7
//#define OLED_CLK   D5
//#define OLED_DC    D2
//#define OLED_CS    D8
//#define OLED_RESET D1
//Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT,
//  OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS);
 
void setup() {
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
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
  Serial.println(F("Initialized!"));
 
  // Show initial display buffer contents on the screen --
  display.clearDisplay();
  display.drawBitmap(0, 0, batman, 32, 13, WHITE);
 
  display.display();
}
 
void loop() {
}
