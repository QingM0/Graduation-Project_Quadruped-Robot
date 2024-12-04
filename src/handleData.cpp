#include "combined.h"

const char *data_ca =
    "-----BEGIN CERTIFICATE-----\n"
    "MIIFBTCCAu2gAwIBAgIQS6hSk/eaL6JzBkuoBI110DANBgkqhkiG9w0BAQsFADBP\n"
    "MQswCQYDVQQGEwJVUzEpMCcGA1UEChMgSW50ZXJuZXQgU2VjdXJpdHkgUmVzZWFy\n"
    "Y2ggR3JvdXAxFTATBgNVBAMTDElTUkcgUm9vdCBYMTAeFw0yNDAzMTMwMDAwMDBa\n"
    "Fw0yNzAzMTIyMzU5NTlaMDMxCzAJBgNVBAYTAlVTMRYwFAYDVQQKEw1MZXQncyBF\n"
    "bmNyeXB0MQwwCgYDVQQDEwNSMTAwggEiMA0GCSqGSIb3DQEBAQUAA4IBDwAwggEK\n"
    "AoIBAQDPV+XmxFQS7bRH/sknWHZGUCiMHT6I3wWd1bUYKb3dtVq/+vbOo76vACFL\n"
    "YlpaPAEvxVgD9on/jhFD68G14BQHlo9vH9fnuoE5CXVlt8KvGFs3Jijno/QHK20a\n"
    "/6tYvJWuQP/py1fEtVt/eA0YYbwX51TGu0mRzW4Y0YCF7qZlNrx06rxQTOr8IfM4\n"
    "FpOUurDTazgGzRYSespSdcitdrLCnF2YRVxvYXvGLe48E1KGAdlX5jgc3421H5KR\n"
    "mudKHMxFqHJV8LDmowfs/acbZp4/SItxhHFYyTr6717yW0QrPHTnj7JHwQdqzZq3\n"
    "DZb3EoEmUVQK7GH29/Xi8orIlQ2NAgMBAAGjgfgwgfUwDgYDVR0PAQH/BAQDAgGG\n"
    "MB0GA1UdJQQWMBQGCCsGAQUFBwMCBggrBgEFBQcDATASBgNVHRMBAf8ECDAGAQH/\n"
    "AgEAMB0GA1UdDgQWBBS7vMNHpeS8qcbDpHIMEI2iNeHI6DAfBgNVHSMEGDAWgBR5\n"
    "tFnme7bl5AFzgAiIyBpY9umbbjAyBggrBgEFBQcBAQQmMCQwIgYIKwYBBQUHMAKG\n"
    "Fmh0dHA6Ly94MS5pLmxlbmNyLm9yZy8wEwYDVR0gBAwwCjAIBgZngQwBAgEwJwYD\n"
    "VR0fBCAwHjAcoBqgGIYWaHR0cDovL3gxLmMubGVuY3Iub3JnLzANBgkqhkiG9w0B\n"
    "AQsFAAOCAgEAkrHnQTfreZ2B5s3iJeE6IOmQRJWjgVzPw139vaBw1bGWKCIL0vIo\n"
    "zwzn1OZDjCQiHcFCktEJr59L9MhwTyAWsVrdAfYf+B9haxQnsHKNY67u4s5Lzzfd\n"
    "u6PUzeetUK29v+PsPmI2cJkxp+iN3epi4hKu9ZzUPSwMqtCceb7qPVxEbpYxY1p9\n"
    "1n5PJKBLBX9eb9LU6l8zSxPWV7bK3lG4XaMJgnT9x3ies7msFtpKK5bDtotij/l0\n"
    "GaKeA97pb5uwD9KgWvaFXMIEt8jVTjLEvwRdvCn294GPDF08U8lAkIv7tghluaQh\n"
    "1QnlE4SEN4LOECj8dsIGJXpGUk3aU3KkJz9icKy+aUgA+2cP21uh6NcDIS3XyfaZ\n"
    "QjmDQ993ChII8SXWupQZVBiIpcWO4RqZk3lr7Bz5MUCwzDIA359e57SSq5CCkY0N\n"
    "4B6Vulk7LktfwrdGNVI5BsC9qqxSwSKgRJeZ9wygIaehbHFHFhcBaMDKpiZlBHyz\n"
    "rsnnlFXCb5s8HKn5LsUgGvB24L7sGNZP2CX7dhHov+YhD+jozLW2p9W4959Bz2Ei\n"
    "RmqDtmiXLnzqTpXbI+suyCsohKRg6Un0RC47+cpiVwHiXZAW+cn8eiNIjqbVgXLx\n"
    "KPpdzvvtTnOPlC7SQZSYmdunr3Bf9b77AiC/ZidstK36dRILKz7OA54=\n"
    "-----END CERTIFICATE-----\n";

SoftwareSerial mySerial(19, 18); // RX, TX
HTTPClient http;
String serialValue;
String apiValue;
// 处理串口通信和服务器数据
void handleCommunicationAndData()
{
    if (mySerial.available())
    {
        serialValue = mySerial.readString();
    }
    else
    {
        fetchAPIData();
    }

    if (!serialValue.isEmpty())
    {
        processValues(serialValue);
    }
    else if (!apiValue.isEmpty())
    {
        processValues(apiValue);
    }
}

void fetchAPIData()
{
    http.begin("https://test.qingmo.moe/data", data_ca); // 开始连接

    int httpCode = http.GET(); // 发送GET请求

    if (httpCode == HTTP_CODE_OK) // 如果请求成功
    {
        String payload = http.getString();
        Serial.println("服务器返回的数据: " + payload); // 输出获取到的数据

        // 解析JSON数组数据
        StaticJsonDocument<200> doc;
        deserializeJson(doc, payload);
        JsonArray array = doc.as<JsonArray>();    // 将JSON解析为数组
        int valueFromServer = array[0]["number"]; // 获取数组中的number字段
        apiValue = String(valueFromServer);       // 将服务器的值保存为字符串
        Serial.print("API获取到的value: ");
        Serial.println(apiValue);
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
    http.begin("https://test.qingmo.moe/clear"); // 连接清除端点
    http.addHeader("Content-Type", "application/json");
    int httpCodeDelete = http.sendRequest("DELETE");
    serialValue = "";
    apiValue = "";

    if (httpCodeDelete == HTTP_CODE_OK)
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
     int intValue = value.toInt();
    if (intValue < 0 || intValue > 11)
    {
        sendDeleteRequest();
        Serial.println("接收到无效的值，已发送DELETE请求: " + intValue);
        return; // 结束函数
    }
    // 使用switch语句
    switch (intValue)
    {
    case 1:
        UI_display_weather();
        delay(3000);
        getHitokoto();
        sendDeleteRequest();
        break;
    case 2:
        zc();
        robot_position();
        getHitokoto();
        sendDeleteRequest();
        break;
    case 3:
        nh();
        for (int i = 0; i < 2; i++)
        {
            robot_Forward();
        }
        getHitokoto();
        sendDeleteRequest();
        break;
    case 4:
        la();
        for (int i = 0; i < 2; i++)
        {
            robot_Backward();
        }
        getHitokoto();
        sendDeleteRequest();
        break;
    case 5:
        gp();
        robot_Turn_left();
        getHitokoto();
        sendDeleteRequest();
        break;
    case 6:
        yb();
        robot_Turn_Right();
        getHitokoto();
        sendDeleteRequest();
        break;
    case 7:
        tx();
        robot_Dancing1();
        getHitokoto();
        sendDeleteRequest();
        break;
    case 8:
        sz();
        robot_Dancing2();
        getHitokoto();
        sendDeleteRequest();
        break;
    case 9:
        yh();
        robot_Dancing3();
        getHitokoto();
        sendDeleteRequest();
        break;
    case 10:
        sj();
        robot_sleep();
        getHitokoto();
        sendDeleteRequest();
        break;
    case 11:
        robot_fuwei();
        getHitokoto();
        sendDeleteRequest();
        break;
    default:
        UI_display_time();
        Serial.println("未知的值: " + value);
        break;
    }

    Serial.print("处理的value: ");
    Serial.println(value);
}