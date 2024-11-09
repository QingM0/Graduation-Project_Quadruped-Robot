#include "combined.h"
#include "AHT10.h"
// #include <U8g2lib.h>
// #include <ArduinoJson.h>
// #include <Adafruit_GFX.h>

// ArduinoJson::V704PB2::JsonDocument weatherData;

int i = 0;
void weather_display()
{
    getqweather();

    U8G2.setCursor(5, 15);
    U8G2.print("天气: " + saved_qweather_text);

    U8G2.setCursor(5, 30);
    U8G2.print("温度: " + saved_qweather_temp + "°C");

    // U8G2.setCursor(5, 60);
    // U8G2.print("风速: " + windSpeed + "km/h");
}

void  AHT10_display()
{
    Wire.begin();
    if (!AHT10::begin())
    {
        // Serial.println(F("AHT10 not detected!"));
        // Serial.flush();
        //  ESP.deepSleep(0);
    }
    float temp, hum;

    if (AHT10::measure(&temp, &hum))
    {
        U8G2.setCursor(5, 45);
        U8G2.print("室内温度 " + String(temp) + "°C");
        U8G2.setCursor(5, 60);
        U8G2.print("室内湿度 " + String(hum) + "%");
        
        Serial.println(temp);
        Serial.println(hum);
    }
    else
    {
        Serial.println(F("AHT10 read error!"));
    }
}
void Hitokoto_display()
{
    U8G2.setFont(u8g2_font_wqy12_t_gb2312);
    U8G2.setCursor(5, 40);
    U8G2.print(saved_Hitokoto);
    Serial.println("句子: " + saved_Hitokoto);
    U8G2.setCursor(30, 55);
    U8G2.print("--");
    U8G2.setCursor(35, 55);
    U8G2.print(saved_Hitokoto_From);
}
void UI_display_time()
{
    U8G2.setFont(u8g2_font_wqy16_t_chinese3);
    String time = time_1();
    U8G2.clearBuffer();
    U8G2.setCursor(40, 20);
    U8G2.print(time);
    Hitokoto_display();
    U8G2.sendBuffer();
    Serial.println("pm1");
}
void UI_display_weather()
{
    U8G2.setFont(u8g2_font_wqy12_t_gb2312);
    U8G2.clearBuffer();
    AHT10_display();
    weather_display();
    U8G2.sendBuffer();
}
