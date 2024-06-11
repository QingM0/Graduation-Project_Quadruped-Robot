#include "combined.h"
#include "AHT10.h"
#include <U8g2lib.h>
#include <ArduinoJson.h>
//#include <Arduino.h>
#include <Adafruit_GFX.h>

// 声明 tft
extern U8G2_SSD1306_128X64_NONAME_F_SW_I2C U8G2;
ArduinoJson::V704PB2::JsonDocument weatherData;
int i = 0;
void weather_display()
{
    // U8G2.clearBuffer();
    // U8G2.setFont(u8g2_font_wqy12_t_chinese2);
    if (i == 0)
    {
        i++;
        weatherData = getweather();
    }

    U8G2.setCursor(5, 15);
    String text = weatherData["now"]["text"].as<String>();
    U8G2.print("天气: " + text);

    U8G2.setCursor(5, 30);
    String temp = weatherData["now"]["temp"].as<String>();
    U8G2.print("温度: " + temp + "°C");

    // U8G2.setCursor(5, 60);
    // String windSpeed = weatherData["now"]["windSpeed"].as<String>();
    // U8G2.print("风速: " + windSpeed + "km/h");

    // U8G2.sendBuffer();
    //  tft.unloadFont();
}

void AHT10_display()
{
    //Serial.begin(9600);
    Wire.begin();
    if (!AHT10::begin())
    {
        //Serial.println(F("AHT10 not detected!"));
        //Serial.flush();
        // ESP.deepSleep(0);
    }
    float temp, hum;

    if (AHT10::measure(&temp, &hum))
    {
        U8G2.setCursor(5, 45);
        U8G2.print("室内温度 " + String(temp) + "°C");
        U8G2.setCursor(5, 60);
        U8G2.print("室内湿度 " + String(hum)+ "%");
    }
    else
    {
        Serial.println(F("AHT10 read error!"));
    }
}

void UI_display()
{
    U8G2.setFont(u8g2_font_wqy12_t_gb2312);
    // U8G2.drawLine(0, 27, 128, 27);
    String time = timeinfo();
    U8G2.clearBuffer();
    U8G2.setCursor(64, 10);
    U8G2.print(time);
    AHT10_display();
    weather_display();
    U8G2.sendBuffer();
    // delay(100);
}