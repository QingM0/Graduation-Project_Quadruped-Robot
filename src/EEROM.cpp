#include "combined.h"
// 保存WiFi信息到EEPROM
void saveWiFiToEEPROM(String ssid, String password)
{
    Serial.println("保存WiFi信息到EEPROM...");

    for (int i = 0; i < ssid.length(); i++)
    {
        EEPROM.write(i, ssid[i]);
    }
    EEPROM.write(ssid.length(), '\0');

    for (int i = 0; i < password.length(); i++)
    {
        EEPROM.write(32 + i, password[i]);
    }
    EEPROM.write(32 + password.length(), '\0');

    EEPROM.commit();
}

// 从EEPROM读取WiFi信息
void readWiFiFromEEPROM()
{
    Serial.println("从EEPROM读取WiFi信息...");

    for (int i = 0; i < 32; i++)
    {
        ssid[i] = EEPROM.read(i);
    }

    for (int i = 0; i < 32; i++)
    {
        password[i] = EEPROM.read(32 + i);
    }

    Serial.print("SSID: ");
    Serial.println(ssid);
    Serial.print("Password: ");
    Serial.println(password);
}
