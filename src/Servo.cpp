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
    const int servoPin1 = 21;
    const int servoPin2 = 33;
    const int servoPin3 = 25;
    const int servoPin4 = 26;
    const int servoPin5 = 27;
    const int servoPin6 = 14;
    const int servoPin7 = 12;
    const int servoPin8 = 13;

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

/*----------动作函数----------*/

// |   7  |             |   6  |
//  ----- -----   ----- -----
//       |  3   | |  2   |
//        -----   -----
//       |   1  | |  0   |
//  ----- -----   ----- -----
// |  5   |             |  4   |

void sleep()
{
  servo4.write(90);
  delay(100);
  servo5.write(90);
  delay(100);
  servo6.write(90);
  delay(100);
  servo7.write(90);
  
}