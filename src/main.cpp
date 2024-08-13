#define ps2_x 35
#define ps2_y 32
#define ps2_w 4
// #include <Arduino.h>
// #include <U8g2lib.h>
// #include <WiFi.h>
// #include <Adafruit_GFX.h>
#include "combined.h"
// #include "AHT10.h"
#include "time.h"

U8G2_SSD1306_128X64_NONAME_F_SW_I2C U8G2(U8G2_R0, /* clock=*/22, /* data=*/21, /* reset=*/16);

const char *ssid = "#283446";
const char *password = "qingmo_1";
int state = 1;
unsigned long previousMillis = 0; // 上次检查的时间
const long interval = 1500;       // 定时器间隔为3秒
int ADC_X = 0;
int ADC_Y = 0;
int ADX_W = 0;

// int wifiStatus = 0;
// struct tm timeinfo;
void setup()
{
    pinMode(ps2_x, INPUT);
    pinMode(ps2_y, INPUT);
    pinMode(ps2_w, INPUT_PULLUP);
    WiFi.begin(ssid, password, 6);
    Serial.begin(9600);
    U8G2.begin();
    U8G2.enableUTF8Print();
    U8G2.setFont(u8g2_font_wqy12_t_chinese2);
    while (WiFi.status() != WL_CONNECTED)
    {
        U8G2.clearBuffer();
        U8G2.setFont(u8g2_font_wqy12_t_gb2312);
        U8G2.setCursor(5, 20);
        U8G2.print("正在联网...");
        U8G2.sendBuffer();
    }
    configTime(60 * 60 * 8, 0, "ntp.aliyun.com"); // 用的阿里云的服务器
    // printLocalTime();
    Serial.println("连接成功");
    Serial.print("IP 地址：");
    Serial.println(WiFi.localIP());
}

void loop()
{
    unsigned long currentMillis = millis();

    if (currentMillis - previousMillis >= interval)
    {
        // 保存上次检查的时间
        previousMillis = currentMillis;

        int ADC_X = analogRead(ps2_x);
        int ADC_Y = analogRead(ps2_y);
        int ADX_W = digitalRead(ps2_w);

        Serial.printf("x = %d, y = %d state = %d \n", ADC_X, ADC_Y, state);
        // while (ADC_X >= 4000 );
        if (ADC_X <= 0 && ADC_Y > 1000) //&& ADC_Y > 1000
    {
        delay(100);
        if (ADC_X <= 0 && ADC_Y > 1000) //&& ADC_Y > 1000
        {
            delay(10);
            state++;
            // while (ADC_X  <= 0 );
        }
    }

    if (ADC_X >= 4000 && ADC_Y > 1000) //&& ADC_Y > 1000
    {
        delay(100);
        if (ADC_X >= 4000 && ADC_Y > 1000) //&& ADC_Y > 1000
        {
            delay(10);
            state--;
        }
    }
    }
    if (state == 1)
    {
        UI_display_main();
    }
    if (state == 0)
    {
        UI_display_0();
    }
    if (state == 2)
    {
        UI_display_2();
    }

    if (state > 2)
    {
        state = 0;
    }

    if (state < 0)
    {
        state = 2;
    }
}