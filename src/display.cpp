#include "combined.h"
#include <U8g2lib.h>
#include <ArduinoJson.h>

// 声明 tft
extern U8G2_SSD1306_128X64_NONAME_F_SW_I2C U8G2;

void weather_display()
{
    //U8G2.clearBuffer();
    //U8G2.setFont(u8g2_font_wqy12_t_chinese2);

    ArduinoJson::V704PB2::JsonDocument weatherData = getweather();

    U8G2.setCursor(5,20);
    String text = weatherData["now"]["text"].as<String>();
    U8G2.print("天气: " + text);

    U8G2.setCursor(5, 30);
    String temp = weatherData["now"]["temp"].as<String>();
    U8G2.print("温度: " + temp + "度");

    // U8G2.setCursor(5, 60);
    // String windSpeed = weatherData["now"]["windSpeed"].as<String>();
    // U8G2.print("风速: " + windSpeed + "km/h");

    //U8G2.sendBuffer();
    // tft.unloadFont();
}

void UI_display()
{
    U8G2.setFont(u8g2_font_wqy12_t_chinese1);
    // U8G2.drawLine(0, 27, 128, 27);
    String time = timeinfo();
    U8G2.clearBuffer();
    U8G2.setCursor(64, 10);
    U8G2.print(time);
    weather_display();
    U8G2.sendBuffer();
    //delay(100);
}