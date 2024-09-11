#include "combined.h"
WebServer server(80);                   // HTTP服务器
const char *apSSID = "ESP32_Config_AP"; // AP模式的SSID

String ssidInput = "";
String passwordInput = "";

char ssid[32] = "";
char password[32] = "";

// 开启AP模式
void startAPMode()
{
    WiFi.softAP(apSSID); // 启动AP模式
    Serial.println("AP模式已启动");
    Serial.print("AP IP 地址: ");
    Serial.println(WiFi.softAPIP());

    // 设置网页请求处理
    server.begin();
    server.on("/", handleRoot);
    server.on("/submit", handleFormSubmission);
    Serial.println("Web服务器已启动");
}

void handleRoot()
{
    // 创建简单的WiFi配置网页
    String html = "<!DOCTYPE html>";
    html += "<html><head>";
    html += "<meta charset=\"UTF-8\">";
    html += "<title>WiFi 配置</title>";
    html += "</head><body><h1>WiFi 配置</h1>";
    html += "<form action=\"/submit\" method=\"post\">";
    html += "SSID: <input type=\"text\" name=\"ssid\"><br>";
    html += "Password: <input type=\"password\" name=\"password\"><br>";
    html += "<input type=\"submit\" value=\"保存\">";
    html += "</form></body></html>";

    server.send(200, "text/html", html);
}

void handleFormSubmission()
{
    String ssidInput = server.arg("ssid");
    String passwordInput = server.arg("password");

    saveWiFiToEEPROM(ssidInput, passwordInput);

    // 创建带有UTF-8编码的网页，提示保存成功并将重启
    String html = "<!DOCTYPE html>";
    html += "<html><head>";
    html += "<meta charset=\"UTF-8\">";                          // 确保网页使用UTF-8编码
    html += "<meta http-equiv=\"refresh\" content=\"3;url=/\">"; // 3秒后重定向到主页
    html += "<title>保存成功</title>";
    html += "</head><body>";
    html += "<h1>保存成功！3秒后自动重启...</h1>";
    html += "</body></html>";

    server.send(200, "text/html", html);

    delay(3000);   // 等待3秒
    ESP.restart(); // 重启设备
}

void connectToWiFi()
{
    WiFi.begin(ssid, password);
    unsigned long startTime = millis();
    while (WiFi.status() != WL_CONNECTED && millis() - startTime < 10000)
    { // 10秒超时
        delay(500);
        Serial.print(".");
    }

    if (WiFi.status() == WL_CONNECTED)
    {
        Serial.println("WiFi连接成功");
        Serial.print("IP 地址: ");
        Serial.println(WiFi.localIP());
        configTime(60 * 60 * 8, 0, "ntp.aliyun.com"); // 用的阿里云的NTP服务器
        getqweather();                                // 获取天气
        getHitokoto();                                // 获取一言
    }
    else
    {
        Serial.println("WiFi连接失败，开启AP模式");
        startAPMode();
    }
}