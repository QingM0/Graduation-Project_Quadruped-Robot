#ifndef COMBINED_H
#define COMBINED_H

#include <ArduinoJson.h>
#include <Arduino.h>
#include <U8g2lib.h>
#include <WiFi.h>
#include <Adafruit_GFX.h>
#include <SoftwareSerial.h>
#include "AHT10.h"
#include "time.h"

void getHitokoto();
void getqweather();

void weather_display();
void UI_display_time();
void UI_display_weather();
String time_1();

#endif // COMBINED_H
