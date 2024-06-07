#ifndef COMBINED_H
#define COMBINED_H

#include <ArduinoJson.h>

ArduinoJson::JsonDocument getyiyang();
void weather_display();
void UI_display();
String timeinfo();
ArduinoJson::V704PB2::JsonDocument getweather();

#endif