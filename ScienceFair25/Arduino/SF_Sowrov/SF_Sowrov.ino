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

  delay(1000);
  
}

void loop() {
  display.clearDisplay();

  // DISPLAY =====================================================
  display.setTextSize(1.5);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  // display.println("ROBOTICS CLUB");
  // display.setTextSize(1);
  display.println("Piezo\nVoltage: 3.14V");
  display.println("Battery level: 72%");
  display.println("Status: Charging...");
  
  display.display();

  delay(2000); // let the visitors see his/her own height for 20 seconds
  
}

