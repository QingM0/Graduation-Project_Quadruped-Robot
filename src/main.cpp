#include <Arduino.h>
#include <U8g2lib.h>
#include <WiFi.h>
#include <Adafruit_GFX.h>
#include "combined.h"

U8G2_SSD1306_128X64_NONAME_F_SW_I2C U8G2(U8G2_R0, /* clock=*/22, /* data=*/21, /* reset=*/16);

const char *ssid = "#283446";
const char *password = "qingmo_1";
int wifiStatus = 0;

void setup()
{
    WiFi.begin(ssid, password, 6);
    Serial.begin(115200);
    U8G2.begin();
    U8G2.enableUTF8Print();
    U8G2.setFont(u8g2_font_wqy12_t_chinese2);
    while (WiFi.status() != WL_CONNECTED)
    {
        U8G2.clearBuffer();
        delay(100);
        // U8G2.setCursor(wifiStatus, 20);
        U8G2.print("."); // wifiStatus, 5,
        // wifiStatus += 5;
        U8G2.sendBuffer();
    }
    Serial.println("连接成功");
    Serial.print("IP 地址：");
    Serial.println(WiFi.localIP());
    //getyiyang();
}

void loop()
{
     UI_display();
}
