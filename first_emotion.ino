#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <WiFi.h>
#include "time.h"

// ---------------- OLED ----------------
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

const char* ssid = "XXXXXXX";
const char* password = "XXXXXXXXX";

const char* ntpServer = "pool.ntp.org";
const long gmtOffset_sec = 19800; // India
const int daylightOffset_sec = 0;

// ---------------- EMOTION ----------------
enum Emotion {
  HAPPY,
  SLEEPY,
  THINKING,
  NORMAL
};

Emotion currentEmotion = NORMAL;
unsigned long lastChange = 0;

// ---------------- MOTIVATION ----------------
String motivation[] = {
  "Love u oshii!",
  "She dreamed in green",
  "Keep building",
  "Take a break",
  "Proud of you"
};

unsigned long lastMotivation = 0;

// =========================================================================
// CRITICAL FIX: Forward Declarations (Inse 'not declared in this scope' theek hoga)
// =========================================================================
void bootAnimation();
void connectWifi();
void drawEmotion(Emotion mood);
void showMotivation();
void checkReminder();
void displayMessage(String msg);
void drawNormal();
void drawHappy();
void drawSleepy();
void drawThinking();

// ---------------- SETUP ----------------
void setup() {
  Serial.begin(9600);
  Wire.begin(21, 22);

  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("OLED failed");
    while(true);
  }

  display.clearDisplay();
  display.setTextColor(SSD1306_WHITE);

  bootAnimation();
  connectWifi();
}

// ---------------- LOOP ----------------
void loop() {
  // change emotions every 4 sec
  if(millis() - lastChange > 4000) {
    int mood = random(0, 4);
    currentEmotion = (Emotion)mood;
    lastChange = millis();
  }

  drawEmotion(currentEmotion);

  // motivation every 20 sec test
  if(millis() - lastMotivation > 20000) { 
    showMotivation();
    lastMotivation = millis();
  }

  checkReminder();
  delay(100);
}

// ---------------- WIFI ----------------
void connectWifi() {
  display.clearDisplay();
  display.setTextSize(1);
  display.setCursor(10, 25);
  display.println("Connecting...");
  display.display();

  WiFi.begin(ssid, password);
  int attempts = 0;

  while(WiFi.status() != WL_CONNECTED && attempts < 20) {
    delay(500);
    Serial.print(".");
    attempts++;
  }

  display.clearDisplay();
  display.setCursor(20, 25);

  if(WiFi.status() == WL_CONNECTED) {
    configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
    display.println("Connected!");
  } else {
    display.println("Offline Mode");
  }
  display.display();
  delay(1000);
}

// ---------------- BOOT ----------------
void bootAnimation() {
  display.clearDisplay();
  display.setTextSize(2);
  display.setCursor(35, 20);
  display.println("Oshii");
  display.display();
  delay(2000);
}

// ---------------- FACE SYSTEM ----------------
void drawEmotion(Emotion mood) {
  display.clearDisplay();

  switch(mood) {
    case HAPPY:
      drawHappy();
      break;
    case SLEEPY:
      drawSleepy();
      break;
    case THINKING:
      drawThinking();
      break;
    default:
      drawNormal();
  }
  display.display();
}

// normal
void drawNormal() {
  display.fillCircle(40, 32, 10, SSD1306_WHITE);
  display.fillCircle(88, 32, 10, SSD1306_WHITE);
}

// happy
void drawHappy() {
  display.fillCircle(40, 28, 10, SSD1306_WHITE);
  display.fillCircle(88, 28, 10, SSD1306_WHITE);

  // smile
  display.drawLine(50, 45, 55, 50, SSD1306_WHITE);
  display.drawLine(55, 50, 65, 52, SSD1306_WHITE);
  display.drawLine(65, 52, 75, 50, SSD1306_WHITE);
  display.drawLine(75, 50, 80, 45, SSD1306_WHITE);
}

// sleepy
void drawSleepy() {
  display.fillRect(30, 32, 25, 5, SSD1306_WHITE);
  display.fillRect(75, 32, 25, 5, SSD1306_WHITE);
}

// thinking
void drawThinking() {
  display.fillCircle(40, 32, 8, SSD1306_WHITE);
  display.fillCircle(88, 32, 12, SSD1306_WHITE);

  display.setTextSize(2);
  display.setCursor(58, 45);
  display.print("?");
}

// ---------------- MOTIVATION ----------------
void showMotivation() {
  int index = random(0, 5);
  displayMessage(motivation[index]);
}

// ---------------- REMINDER ----------------
void checkReminder() {
  struct tm timeinfo;
  if(!getLocalTime(&timeinfo)) {
    return;
  }

  int hour = timeinfo.tm_hour;
  int minute = timeinfo.tm_min;

  if(hour == 7 && minute == 0) {
    displayMessage("Good Morning");
  }

  if(hour == 22 && minute == 30) {
    displayMessage("Sleep soon :)");
  }
}

// ---------------- TEXT ----------------
void displayMessage(String msg) {
  display.clearDisplay();
  display.setTextSize(1);
  
  // Text ko screen ke center mein auto-align karne ke liye
  int16_t x1, y1;
  uint16_t w, h;
  display.getTextBounds(msg, 0, 0, &x1, &y1, &w, &h);
  
  display.setCursor((SCREEN_WIDTH - w) / 2, (SCREEN_HEIGHT - h) / 2);
  display.println(msg);
  display.display();
  delay(3000);
}