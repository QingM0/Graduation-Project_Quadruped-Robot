#ifndef COMBINED_H
#define COMBINED_H

#include <ArduinoJson.h>
#include <Arduino.h>
#include <U8g2lib.h>
#include <WiFi.h>
#include <Adafruit_GFX.h>
#include "AHT10.h"
#include "time.h"

// 使用 JsonDocument，而不指定是 Dynamic 或 Static，以提高灵活性
ArduinoJson::JsonDocument getHitokoto();
ArduinoJson::JsonDocument getqweather();

void weather_display();
void UI_display_main();
void UI_display_0();
void UI_display_2();
String time_1();

#endif // COMBINED_H
