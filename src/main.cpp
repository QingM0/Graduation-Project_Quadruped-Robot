#include "combined.h"
// #include "AHT10.h"
#include "time.h"

U8G2_SSD1306_128X64_NONAME_F_SW_I2C U8G2(U8G2_R0, /* clock=*/22, /* data=*/21, /* reset=*/16);

const char *ssid = "#283446";
const char *password = "qingmo_1";
SoftwareSerial mySerial(19, 18); // RX, TX
String value;
void setup()
{
    Serial.begin(9600);
    mySerial.begin(115200);
    U8G2.begin();
    U8G2.enableUTF8Print();
    U8G2.setFont(u8g2_font_wqy12_t_chinese2);
    WiFi.begin(ssid, password, 6);
    while (WiFi.status() != WL_CONNECTED)
    {
        U8G2.clearBuffer();
        U8G2.setFont(u8g2_font_wqy12_t_gb2312);
        U8G2.setCursor(5, 20);
        U8G2.print("正在联网...");
        U8G2.sendBuffer();
    }

    configTime(60 * 60 * 8, 0, "ntp.aliyun.com"); // 用的阿里云的服务器
    Serial.println("连接成功");
    Serial.print("IP 地址：");
    Serial.println(WiFi.localIP());
    getqweather();
    getHitokoto();
}

void loop()
{
    if (mySerial.available())
    {
        value = (mySerial.readString());
        Serial.println(value); 
        if (value == "1")
        {
            UI_display_time();
        }
        if (value == "2")
        {
            UI_display_weather();
            getHitokoto();
        }
        Serial.print("收到串口1的数据: ");
        Serial.println(value);
        Serial.print("111");
    }
}