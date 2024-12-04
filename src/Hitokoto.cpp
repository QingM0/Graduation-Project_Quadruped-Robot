#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <Arduino.h>

const char *Hitokoto_ca =
    "-----BEGIN CERTIFICATE-----\n"
    "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\n"
    "-----END CERTIFICATE-----\n";

const char *Hitokoto_url = "https://v1.hitokoto.cn/?encode=json&max_length=11";
String response;
String saved_Hitokoto = "";
String saved_Hitokoto_From = "";

void getHitokoto()
{
    HTTPClient http;

    http.begin(Hitokoto_url, Hitokoto_ca);
    int httpCode = http.GET(); // 发送 HTTP 请求

    // 获取响应状态码
    //Serial.printf("HTTP 状态码: %d\n", httpCode);

    if (httpCode == HTTP_CODE_OK)
    {
        // 获取响应正文并存储到 response 变量中
        response = http.getString();
        //Serial.println("响应数据:");
        //Serial.println(response + "\n");
    }
    else
    {
        Serial.println("HTTP 请求失败");
    }

    http.end(); // 结束 HTTP 请求

    // 解析 JSON 数据
    DynamicJsonDocument Hitokoto(1024); // 分配 1024 字节的缓冲区用于解析 JSON 数据
    DeserializationError error = deserializeJson(Hitokoto, response);

    // 检查解析错误
    if (error)
    {
        Serial.print(F("deserializeJson() failed: "));
        Serial.println(error.c_str());
        return;
    }

    // 提取 JSON 数据中的句子和来源
    saved_Hitokoto = Hitokoto["hitokoto"].as<String>();
    saved_Hitokoto_From = Hitokoto["from"].as<String>();

    // 打印句子和来源
    Serial.println("句子: " + saved_Hitokoto);
    Serial.println("来源: " + saved_Hitokoto_From);
}