#include "combined.h"
SoftwareSerial mySerial(19, 18); // RX, TX

String serialValue;
String apiValue;
// 处理串口通信和服务器数据
void handleCommunicationAndData()
{
    // 检查串口通信
    if (mySerial.available())
    {
        serialValue = mySerial.readString();
        // if (!serialValue.isEmpty()) // 检查是否读取到有效数据
        // {
        //     Serial.println("串口数据: " + serialValue);
        // }
    }

    // 获取并处理服务器数据
    fetchAPIData();

    // 如果串口数据存在且有效，则优先处理串口数据
    if (!serialValue.isEmpty())
    {
        processValues(serialValue); // 使用串口数据
        sendDeleteRequest();     // API数据处理后发送DELETE请求
    }
    else if (!apiValue.isEmpty()) // 如果串口数据为空，处理API数据
    {
        processValues(apiValue); // 使用API数据
        sendDeleteRequest();     // API数据处理后发送DELETE请求
    }

    // 清空串口和API数据，以便下一轮读取
    serialValue = "";
    apiValue = "";
}

// 获取服务器数据并存储在 apiValue 中
void fetchAPIData()
{
    HTTPClient http;
    http.begin("https://test.qingmo.moe/data"); // 开始连接

    int httpCode = http.GET(); // 发送GET请求

    if (httpCode > 0) // 如果请求成功
    {
        String payload = http.getString();
        Serial.println("服务器返回的数据: " + payload); // 输出获取到的数据

        // 解析JSON数组数据
        StaticJsonDocument<200> doc;
        DeserializationError error = deserializeJson(doc, payload);

        if (!error)
        {
            JsonArray array = doc.as<JsonArray>(); // 将JSON解析为数组

            int valueFromServer = array[0]["number"]; // 获取数组中的number字段
            apiValue = String(valueFromServer);       // 将服务器的值保存为字符串
            Serial.print("API获取到的value: ");
            Serial.println(apiValue);
        }
        else
        {
            Serial.println("解析JSON时出错");
        }
    }
    else
    {
        Serial.print("HTTP请求失败，错误码: ");
        Serial.println(httpCode);
    }

    http.end(); // 结束HTTP连接
}

// 发送DELETE请求以清除API数据
void sendDeleteRequest()
{
    HTTPClient http;
    http.begin("https://test.qingmo.moe/clear"); // 连接清除端点
    http.addHeader("Content-Type", "application/json");
    int httpCodeDelete = http.sendRequest("DELETE");

    if (httpCodeDelete > 0)
    {
        Serial.println("服务器数据已清除");
    }
    else
    {
        Serial.println("清除服务器数据时出现错误");
    }

    http.end(); // 结束HTTP连接
}

// 根据串口或API的值执行操作
void processValues(String value)
{
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

    Serial.print("处理的value: ");
    Serial.println(value);
}