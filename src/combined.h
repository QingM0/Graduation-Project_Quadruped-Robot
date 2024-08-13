#ifndef COMBINED_H
#define COMBINED_H

#include <ArduinoJson.h>
#include <Arduino.h>
#include <U8g2lib.h>
#include <WiFi.h>
#include <Adafruit_GFX.h>
//#include "combined.h"
#include "AHT10.h"
#include "time.h"

ArduinoJson::JsonDocument getyiyang();
void weather_display();
void UI_display_main();
void UI_display_0();
void UI_display_2();
String time_1();
ArduinoJson::V704PB2::JsonDocument getweather();

#endif