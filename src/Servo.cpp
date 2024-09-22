#include "combined.h"
#define MAX_WIDTH 2500
#define MIN_WIDTH 500
Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;
Servo servo5;
Servo servo6;
Servo servo7;
Servo servo8;

void servo_initialization()
{
  // 定义每个舵机连接的引脚
  const int servoPin8 = 2;
  const int servoPin7 = 4;
  const int servoPin6 = 16;
  const int servoPin5 = 17;
  const int servoPin4 = 25;
  const int servoPin3 = 33;
  const int servoPin2 = 32;
  const int servoPin1 = 26;

  // 分配所有可用的PWM定时器
  ESP32PWM::allocateTimer(0);
  ESP32PWM::allocateTimer(1);

  // 设置舵机的频率和附加到引脚
  servo1.setPeriodHertz(50);
  servo1.attach(servoPin1, MIN_WIDTH, MAX_WIDTH);

  servo2.setPeriodHertz(50);
  servo2.attach(servoPin2, MIN_WIDTH, MAX_WIDTH);

  servo3.setPeriodHertz(50);
  servo3.attach(servoPin3, MIN_WIDTH, MAX_WIDTH);

  servo4.setPeriodHertz(50);
  servo4.attach(servoPin4, MIN_WIDTH, MAX_WIDTH);

  servo5.setPeriodHertz(50);
  servo5.attach(servoPin5, MIN_WIDTH, MAX_WIDTH);

  servo6.setPeriodHertz(50);
  servo6.attach(servoPin6, MIN_WIDTH, MAX_WIDTH);

  servo7.setPeriodHertz(50);
  servo7.attach(servoPin7, MIN_WIDTH, MAX_WIDTH);

  servo8.setPeriodHertz(50);
  servo8.attach(servoPin8, MIN_WIDTH, MAX_WIDTH);
}

//  -----               -----
// | D1  |             | D5 |
// |IO18 |             |IO0 |
//  ----- -----   ----- -----
//       | D2  | | D6  |
//       |IO19 | |IO1  |
//        -----   -----
//       | D3  | | D7  |
//       | IO8 | |IO12 |
//  ----- -----   ----- -----
// | D4  |             | D8  |
// |IO9  |             |IO13 |
//  -----               -----

void bot_sleep()
{
  servo1.write(145);
  servo2.write(45);
  servo3.write(135);
  servo4.write(25);
  servo5.write(25);
  servo6.write(135);
  servo7.write(45);
  servo8.write(145);
}
void bot_test()
{
  servo1.write(145);
  servo2.write(45);
  servo3.write(135);
  servo4.write(25);
  servo5.write(25);
  servo6.write(135);
  servo7.write(45);
  servo8.write(145);
  delay(500);
  servo1.write(145 - 20);
  servo2.write(45);
  servo3.write(135);
  servo4.write(25 + 20);
  servo5.write(25 + 20);
  servo6.write(135);
  servo7.write(45);
  servo8.write(145 - 20);
}

void bot_test1()
{
  servo1.write(145);
  servo2.write(45);
  servo3.write(135);
  servo4.write(25);
  servo5.write(25);
  servo6.write(135);
  servo7.write(45);
  servo8.write(145);
  delay(200);
  servo1.write(145 + 20);
  servo2.write(45);
  servo3.write(135);
  servo4.write(25);
  servo5.write(25);
  servo6.write(135);
  servo7.write(45 - 45);
  servo8.write(145 + 20);
  delay(200);
  servo1.write(145);
  servo2.write(45);
  servo3.write(135);
  servo4.write(25);
  servo5.write(25);
  servo6.write(135);
  servo7.write(45 - 45);
  servo8.write(145);
  delay(200);
  servo1.write(145);
  servo2.write(45);
  servo3.write(135);
  servo4.write(25 - 20);
  servo5.write(25 - 20);
  servo6.write(135);
  servo7.write(45 - 45);
  servo8.write(145);
  delay(200);
  servo1.write(145);
  servo2.write(45 - 45);
  servo3.write(135 + 45);
  servo4.write(25 - 20);
  servo5.write(25 - 20);
  servo6.write(135);
  servo7.write(45);
  servo8.write(145);
  delay(200);
  servo1.write(145);
  servo2.write(45 - 45);
  servo3.write(135 + 45);
  servo4.write(25);
  servo5.write(25);
  servo6.write(135);
  servo7.write(45);
  servo8.write(145);
  delay(200);
  servo1.write(145 + 20);
  servo2.write(45);
  servo3.write(135 + 45);
  servo4.write(25);
  servo5.write(25);
  servo6.write(135);
  servo7.write(45);
  servo8.write(145 + 20);
  delay(200);
  servo1.write(145 + 20);
  servo2.write(45);
  servo3.write(135);
  servo4.write(25);
  servo5.write(25);
  servo6.write(135 + 45);
  servo7.write(45);
  servo8.write(145 + 20);
  delay(200);
  servo1.write(145);
  servo2.write(45);
  servo3.write(135);
  servo4.write(25);
  servo5.write(25);
  servo6.write(135 + 45);
  servo7.write(45);
  servo8.write(145);
  delay(200);
  servo1.write(145);
  servo2.write(45);
  servo3.write(135);
  servo4.write(25);
  servo5.write(25 - 20);
  servo6.write(135 + 45);
  servo7.write(45);
  servo8.write(145);
  delay(200);
  servo1.write(145);
  servo2.write(45);
  servo3.write(135);
  servo4.write(25);
  servo5.write(25);
  servo6.write(135);
  servo7.write(45);
  servo8.write(145);
}