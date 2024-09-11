#include "combined.h"
#define MAX_WIDTH 2500
#define MIN_WIDTH 500
Servo servo1;
Servo servo2;
Servo servo3;
Servo servo4;
// Servo servo5;
// Servo servo6;
// Servo servo7;
// Servo servo8;

void servo_initialization()
{
    // 定义每个舵机连接的引脚
    const int servoPin1 = 32;
    const int servoPin2 = 33;
    const int servoPin3 = 25;
    const int servoPin4 = 26;
    // const int servoPin5 = 23;
    // const int servoPin6 = 25;
    // const int servoPin7 = 26;
    // const int servoPin8 = 27;

    // 分配所有可用的PWM定时器
    ESP32PWM::allocateTimer(0);

    // 设置舵机的频率和附加到引脚
    servo1.setPeriodHertz(50);
    servo1.attach(servoPin1, MIN_WIDTH, MAX_WIDTH);

    servo2.setPeriodHertz(50);
    servo2.attach(servoPin2, MIN_WIDTH, MAX_WIDTH);

    servo3.setPeriodHertz(50);
    servo3.attach(servoPin3, MIN_WIDTH, MAX_WIDTH);

    servo4.setPeriodHertz(50);
    servo4.attach(servoPin4, MIN_WIDTH, MAX_WIDTH);

    // servo5.setPeriodHertz(50);
    // servo5.attach(servoPin5, MIN_WIDTH, MAX_WIDTH);

    // servo6.setPeriodHertz(50);
    // servo6.attach(servoPin6, MIN_WIDTH, MAX_WIDTH);

    // servo7.setPeriodHertz(50);
    // servo7.attach(servoPin7, MIN_WIDTH, MAX_WIDTH);

    // servo8.setPeriodHertz(50);
    // servo8.attach(servoPin8, MIN_WIDTH, MAX_WIDTH);
}
void Rbt_Init()
{
    // 创建8个舵机对象
    servo1.write(90);
    servo2.write(90);
    servo3.write(90);
    servo4.write(90);
    delay(100);
}
void move_forward()
{
    servo1.write(135);
    servo4.write(45);
    delay(250);
    servo2.write(45);
    servo3.write(135);
    delay(250);
    servo1.write(90);
    servo4.write(90);
    delay(250);
    servo2.write(90);
    servo3.write(90);

    delay(250);
    
    servo1.write(135);
    servo4.write(45);
    delay(250);
    servo2.write(45);
    servo3.write(135);
    delay(250);
    servo1.write(90);
    servo4.write(90);
    delay(250);
    servo2.write(90);
    servo3.write(90);
}