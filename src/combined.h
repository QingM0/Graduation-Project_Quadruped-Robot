#ifndef COMBINED_H
#define COMBINED_H

#include <ArduinoJson.h>
#include <Arduino.h>
#include <U8g2lib.h>
#include <WiFi.h>
#include <Adafruit_GFX.h>
#include <SoftwareSerial.h>
#include <ESP32Servo.h>
#include <Wire.h>
#include <EEPROM.h>
#include <WebServer.h>
#include <HTTPClient.h>
#include "AHT10.h"
#include "time.h"

void getHitokoto();
void getqweather();

void weather_display();
void UI_display_time();
void UI_display_weather();

void servo_initialization();

void startAPMode();
void connectToWiFi();

void handleRoot();
void handleFormSubmission();

void saveWiFiToEEPROM(String ssid, String password);
void readWiFiFromEEPROM();

String time_1();

extern WebServer server;
extern U8G2_SSD1306_128X64_NONAME_F_SW_I2C U8G2;

extern char password[32];
extern char ssid[32];

extern String saved_Hitokoto;
extern String saved_Hitokoto_From;
extern String saved_qweather_text;
extern String saved_qweather_temp;

// EEPROM大小
#define EEPROM_SIZE 512

#endif // COMBINED_H
