#include "combined.h"
// #include "AHT10.h"
// #include "time.h"

U8G2_SSD1306_128X64_NONAME_F_SW_I2C U8G2(U8G2_R0, /* clock=*/22, /* data=*/21, /* reset=*/16);


unsigned long previousMillis = 0;  // 用于计算时间间隔
const long interval = 2000;        // 每秒请求一次

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
   unsigned long currentMillis = millis();
    
    // 如果WiFi已连接，处理串口通信和数据请求
    if (WiFi.status() == WL_CONNECTED)
    {
        // 每秒请求一次数据并处理串口通信
        if (currentMillis - previousMillis >= interval)
        {
            previousMillis = currentMillis;
            handleCommunicationAndData();  // 处理串口和服务器数据
        }
    }
    else
    {
        server.handleClient();  // WiFi未连接时处理客户端请求
    }
}
