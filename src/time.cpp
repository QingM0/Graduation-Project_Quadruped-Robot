#include <WiFi.h>
#include <WiFiUdp.h>
#include <NTPClient.h>

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "ntp.aliyun.com", 60 * 60 * 8, 60000);
String timeinfo(){
    timeClient.begin();
    timeClient.update();
    //Serial.println(timeClient.getFormattedTime());
    return timeClient.getFormattedTime();
}