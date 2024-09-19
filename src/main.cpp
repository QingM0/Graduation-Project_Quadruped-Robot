#include "combined.h"
// #include "AHT10.h"
//#include "time.h"

U8G2_SSD1306_128X64_NONAME_F_SW_I2C U8G2(U8G2_R0, /* clock=*/22, /* data=*/21, /* reset=*/16);
SoftwareSerial mySerial(19, 18); // RX, TX

String value;

void setup()
{
    Serial.begin(115200);
    mySerial.begin(115200);
    U8G2.begin();
    U8G2.enableUTF8Print();
    U8G2.setFont(u8g2_font_wqy12_t_chinese2);

    // 初始化EEPROM
    EEPROM.begin(EEPROM_SIZE);
    // 读取保存的WiFi信息
    readWiFiFromEEPROM();
    // 初始化舵机
    servo_initialization();
    // 检查并连接WiFi
    if (String(ssid) != "")
    {
        connectToWiFi();
    }
    else
    {
        startAPMode();
    }
}

void loop()
{
    // 如果WiFi已连接，处理串口通信
    if (WiFi.status() == WL_CONNECTED)
    {
        if (mySerial.available())
        {
            value = mySerial.readString();
            Serial.println(value);

            if (value == "1")
            {
                UI_display_time(); 
            }
            else if (value == "2")
            {
                UI_display_weather(); 
                getHitokoto();        
            }
            else if (value == "3")
            {
                // 执行其他操作
            }
            else if (value == "4")
            {
                // 执行其他操作
            }

            Serial.print("收到串口1的数据: ");
            Serial.println(value);
        }
    }
    else
    {
        server.handleClient();
    }
}

