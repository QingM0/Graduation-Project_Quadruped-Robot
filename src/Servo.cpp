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
  const int servoPin4 = 26;
  const int servoPin3 = 25;
  const int servoPin2 = 33;
  const int servoPin1 = 32;

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

void robot_position()
{
  servo1.write(155);
  delay(50);
  servo2.write(45);
  delay(50);
  servo3.write(135);
  delay(50);
  servo4.write(15);
  delay(50);
  servo5.write(15);
  delay(50);
  servo6.write(135);
  delay(50);
  servo7.write(45);
  delay(50);
  servo8.write(155);
  delay(50);
}

void robot_Forward()
{
  servo1.write(145);
  delay(50);
  servo2.write(45);
  delay(50);
  servo3.write(135);
  delay(50);
  servo4.write(25);
  delay(50);
  servo5.write(25);
  delay(50);
  servo6.write(135);
  delay(50);
  servo7.write(45);
  delay(50);
  servo8.write(145);
  delay(100);
  servo1.write(165);
  delay(50);
  servo7.write(0);
  delay(50);
  servo8.write(165);
  delay(100);
  servo1.write(145);
  delay(50);
  servo8.write(145);
  delay(100);
  servo4.write(5);
  delay(50);
  servo5.write(5);
  delay(100);
  servo2.write(0);
  delay(50);
  servo3.write(180);
  delay(50);
  servo7.write(45);
  delay(100);
  servo4.write(25);
  delay(50);
  servo5.write(25);
  delay(100);
  servo1.write(165);
  delay(50);
  servo2.write(45);
  delay(50);
  servo8.write(165);
  delay(100);
  servo3.write(135);
  delay(50);
  servo6.write(180);
  delay(100);
  servo1.write(145);
  delay(50);
  servo8.write(145);
  delay(100);
  servo5.write(5);
  delay(100);
  servo5.write(25);
  delay(50);
  servo6.write(135);
}
void robot_Backward()
{
  servo1.write(145);
  servo2.write(45);
  servo3.write(135);
  servo4.write(25);
  servo5.write(25);
  servo6.write(135);
  servo7.write(45);
  servo8.write(145);
  delay(100);
  servo1.write(165);
  servo2.write(0);
  servo8.write(165);
  delay(100);
  servo1.write(145);
  servo8.write(145);
  delay(100);
  servo4.write(5);
  servo5.write(5);
  delay(100);
  servo2.write(45);
  servo6.write(180);
  servo7.write(0);
  delay(100);
  servo4.write(25);
  servo5.write(25);
  delay(100);
  servo1.write(165);
  servo7.write(0);
  servo8.write(165);
  delay(100);
  servo3.write(180);
  servo6.write(135);
  delay(100);
  servo1.write(145);
  servo8.write(145);
  delay(100);
  servo4.write(5);
  delay(100);
  servo3.write(135);
  servo4.write(25);
  delay(100);
}