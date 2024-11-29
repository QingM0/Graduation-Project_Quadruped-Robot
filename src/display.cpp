#include "combined.h"
#include "emoticons.h"

// 显示坐标和尺寸的常量
const int X_POS = 2;
const int Y_POS = 2;
const int WIDTH = 128;
const int HEIGHT = 64;
// 辅助函数，用于绘制图像
void drawImage(const uint8_t* image) {
    U8G2.clearBuffer();
    U8G2.drawXBMP(X_POS, Y_POS, WIDTH, HEIGHT, image);
    U8G2.sendBuffer();
    delay(20);
}
// 使用辅助函数的具体实现
void yh() { drawImage(youhao); }
void zc() { drawImage(zhengchang); }
void sj() { drawImage(shuijiao); }
void nh() { drawImage(nihao); }
void la() { drawImage(laia); }
void gp() { drawImage(goupao); }
void tx() { drawImage(touxiang); }
void yb() { drawImage(yaobai); }
void sz() { drawImage(shanzi); }
int i = 0;
void weather_display()
{
    getqweather();

    U8G2.setCursor(5, 15);
    U8G2.print("天气: " + saved_qweather_text);

    U8G2.setCursor(5, 30);
    U8G2.print("温度: " + saved_qweather_temp + "°C");

    // U8G2.setCursor(5, 60);
    // U8G2.print("风速: " + windSpeed + "km/h");
}

void Hitokoto_display()
{
    U8G2.setFont(u8g2_font_wqy12_t_gb2312);
    U8G2.setCursor(5, 40);
    U8G2.print(saved_Hitokoto);
    Serial.println("句子: " + saved_Hitokoto);
    U8G2.setCursor(30, 55);
    U8G2.print("--");
    U8G2.setCursor(35, 55);
    U8G2.print(saved_Hitokoto_From);
}
void UI_display_time()
{
    U8G2.setFont(u8g2_font_wqy16_t_chinese3);
    String time = time_1();
    U8G2.clearBuffer();
    U8G2.setCursor(40, 20);
    U8G2.print(time);
    Hitokoto_display();
    U8G2.sendBuffer();
}
void UI_display_weather()
{
    U8G2.setFont(u8g2_font_wqy12_t_gb2312);
    U8G2.clearBuffer();
    weather_display();
    U8G2.sendBuffer();
}
