#include <WiFi.h>
#include <WiFiUdp.h>
#include <NTPClient.h>
#include "time.h"  

// WiFiUDP ntpUDP;
// NTPClient timeClient(ntpUDP, "ntp.aliyun.com",  60 *60 * 8, 60000);

struct tm timeinfo;
String time_1()
{
    if (!getLocalTime(&timeinfo))
    {
        Serial.println("Failed to obtain time");
        return "Failed to obtain time"; // 返回错误信息
    }
    char buffer[80];
    strftime(buffer, sizeof(buffer), "%H:%M", &timeinfo); //%A, %B %d %Y %H:%M:%S
    //Serial.println(buffer); // 打印格式化的时间
    return String(buffer); // 将格式化的时间转换为String并返回
}
// String time_2()
// {
//     if (!getLocalTime(&timeinfo))
//     {
//         Serial.println("Failed to obtain time");
//         return "Failed to obtain time"; // 返回错误信息
//     }
//     char buffer[80];
//     strftime(buffer, sizeof(buffer), "%H:%M", &timeinfo); //%A, %B %d %Y %H:%M:%S
//     //Serial.println(buffer); // 打印格式化的时间
//     return String(buffer); // 将格式化的时间转换为String并返回
// }


// struct tm timeinfo;
// void printLocalTime()
// {
//     if (!getLocalTime(&timeinfo))
//     {
//         Serial.println("Failed to obtain time");
//         return;
//     }
//     Serial.println(&timeinfo, "%A, %B %d %Y %H:%M:%S");
// }