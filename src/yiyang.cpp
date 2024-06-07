#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <Arduino.h>

const char *yiyang_ca =
    "-----BEGIN CERTIFICATE-----\n"
    "MIIGWjCCBUKgAwIBAgIMZPs0hrBg/Xlp/8JSMA0GCSqGSIb3DQEBCwUAMFUxCzAJ\n"
    "BgNVBAYTAkJFMRkwFwYDVQQKExBHbG9iYWxTaWduIG52LXNhMSswKQYDVQQDEyJH\n"
    "bG9iYWxTaWduIEdDQyBSNiBBbHBoYVNTTCBDQSAyMDIzMB4XDTI0MDQxNTAxNDkx\n"
    "MloXDTI1MDUxNzAxNDkxMVowGDEWMBQGA1UEAwwNKi5oaXRva290by5jbjCCASIw\n"
    "DQYJKoZIhvcNAQEBBQADggEPADCCAQoCggEBAMZeSQt6FRHd3HB2ZAu5j0pQPdQ3\n"
    "6fIDrwnKI3w4C45pWzagh/gs0ufQ9XZmmgqkCYknErjTynV4XmCpARXz4tSw4UCN\n"
    "CrKDk8TKjN6jpRB5uGKUK2BiezjxHKE8Lmh7KVAlnS+PbsUVo7jpQd1EvDE8uexy\n"
    "ZxTgr5PJxn13uWwwK2z5whR9RMviCbLNCmTWqxM4JvVP1dL+2jNxzjy29tYlV4Hc\n"
    "elr9DdZpHrZpSec+A7a/xeGKAAnKJn4OhWDB/Lnsf3cihz75sK2X/dnbuNfeaLsy\n"
    "2yUjjgmtp3Jq3OP23N916kx4dAP4nbWD+BHzXwlRTbMitQrjKq98ShfS04UCAwEA\n"
    "AaOCA2UwggNhMA4GA1UdDwEB/wQEAwIFoDAMBgNVHRMBAf8EAjAAMIGZBggrBgEF\n"
    "BQcBAQSBjDCBiTBJBggrBgEFBQcwAoY9aHR0cDovL3NlY3VyZS5nbG9iYWxzaWdu\n"
    "LmNvbS9jYWNlcnQvZ3NnY2NyNmFscGhhc3NsY2EyMDIzLmNydDA8BggrBgEFBQcw\n"
    "AYYwaHR0cDovL29jc3AuZ2xvYmFsc2lnbi5jb20vZ3NnY2NyNmFscGhhc3NsY2Ey\n"
    "MDIzMFcGA1UdIARQME4wCAYGZ4EMAQIBMEIGCisGAQQBoDIKAQMwNDAyBggrBgEF\n"
    "BQcCARYmaHR0cHM6Ly93d3cuZ2xvYmFsc2lnbi5jb20vcmVwb3NpdG9yeS8wRAYD\n"
    "VR0fBD0wOzA5oDegNYYzaHR0cDovL2NybC5nbG9iYWxzaWduLmNvbS9nc2djY3I2\n"
    "YWxwaGFzc2xjYTIwMjMuY3JsMCUGA1UdEQQeMByCDSouaGl0b2tvdG8uY26CC2hp\n"
    "dG9rb3RvLmNuMB0GA1UdJQQWMBQGCCsGAQUFBwMBBggrBgEFBQcDAjAfBgNVHSME\n"
    "GDAWgBS9BbfzipM8c8t5+g+FEqF3lhiRdDAdBgNVHQ4EFgQUuw8oBic3+3KZwXw3\n"
    "xTrgcPDEhWUwggF+BgorBgEEAdZ5AgQCBIIBbgSCAWoBaAB2AKLjCuRF772tm344\n"
    "7Udnd1PXgluElNcrXhssxLlQpEfnAAABjt9xs1IAAAQDAEcwRQIgPq0/Q7J9LpFz\n"
    "Siuu7uJNhzApqdDU5VJK3LAvJO9ldJUCIQCak5nSlaYewhIeTL/C/0c9pOAcC+i3\n"
    "1G9MyFiJW8WtJgB2AObSMWNAd4zBEEEG13G5zsHSQPaWhIb7uocyHf0eN45QAAAB\n"
    "jt9xsy0AAAQDAEcwRQIhANuJvr63iFL6+ZvKRp6dv5sKqvZbhSufQ6AB2gBVY94/\n"
    "AiBk8DeM2lkY5bbomVNU5otB3qyxg9UTAI+zsYPYw+3jZAB2AE51oydcmhDDOFts\n"
    "1N8/Uusd8OCOG41pwLH6ZLFimjnfAAABjt9xtDcAAAQDAEcwRQIgYk10XXYm2Me5\n"
    "dcoN2HQ8tpJ+5jDgmnZZrOXzn2sAYV8CIQDajoFcIo70llAAjHvhXW5i3WRq58hA\n"
    "7SxSPZLb1xQlcTANBgkqhkiG9w0BAQsFAAOCAQEAs5sbzLukz52SGFZ+xdHRe/XD\n"
    "77UMBugggMxrJACTnR5gR5WlsHSjGM9TCB6LY/UuhfXV8VC+0OLD7KS4cyVvjpXT\n"
    "Td0MpxIZmE4HDgv5cH3gUoPhSvifwao5QaJVrH4YtKmKnFYKkBjDpOaT5fobeNQa\n"
    "7wBxA8scZmMr4h7Nosn0CEOdtoJj+wM9rCOFe0kAp3RBO3X5+hS9HRx41Zexbev/\n"
    "fAz4M2yUe1xznOZngcAo5A9flpSgdxIkCg0mz2o+in7H/683ASkljPhQbEJwGFrJ\n"
    "Z3BLuLES3S91zd+6RVEJbXKbpF3gtdDfi65W7PiM80XxeDQYkguqbxepiW9UYg==\n"
    "-----END CERTIFICATE-----\n";

const char *yiyang_url = "https://v1.hitokoto.cn/?encode=text&max_length=10";
ArduinoJson::JsonDocument getyiyang()
{
    HTTPClient http;
    http.begin(yiyang_url, yiyang_ca);

    http.setTimeout(10000);

    int httpCode = http.GET();

    // 获取响应状态码
    Serial.printf("HTTP 状态码: %d", httpCode);

    // 获取响应正文
    String response = http.getString();
    Serial.println("响应数据");
    Serial.println(response);

    http.end();

    // 创建 DynamicJsonDocument 对象
    DynamicJsonDocument doc(1024);

    // 解析 JSON 数据
    deserializeJson(doc, response);
    String text = doc["hitokoto"].as<String>();
     Serial.printf("温度: %d\n", text);
}