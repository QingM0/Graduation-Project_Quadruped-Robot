#include "combined.h"

#define MAX_WIDTH 2500     // 舵机的最大宽度
#define MIN_WIDTH 500      // 舵机的最小宽度
#define SERVO_FREQUENCY 50 // 舵机的频率
#define SERVO_COUNT 8      // 舵机的数量

// 定义舵机数组和对应的引脚数组
Servo servos[SERVO_COUNT];
const int servoPins[SERVO_COUNT] = {32, 33, 25, 26, 17, 16, 4, 2};

// 定义舵机位置结构体，包含舵机位置数组和延时时间
struct ServoPosition
{
    int positions[SERVO_COUNT];
    int delayTime;
};
//  -----               -----
// | D1  |             | D5 |
// |IO32 |             |IO17 |
//  ----- -----   ----- -----
//       | D2  | | D6  |
//       |IO33 | |IO16  |
//        -----   -----
//       | D3  | | D7  |
//       | IO25 | |IO4 |
//  ----- -----   ----- -----
// | D4  |             | D8  |
// |IO26  |             |IO2 |
//  -----               -----
// 定义初始位置
ServoPosition initialPos = {{150, 45, 135, 20, 25, 135, 45, 155}, 50};
ServoPosition fuwei = {{85, 90, 90, 90, 95, 90, 90, 90}, 50};
ServoPosition forwardSteps[] = {
    {{170, 45, 135, 20, 25, 135, 0, 175}, 50},
    {{150, 45, 135, 20, 25, 135, 0, 155}, 50},
    {{150, 45, 135, 0, 5, 135, 0, 155}, 50},
    {{150, 0, 180, 0, 5, 135, 45, 155}, 50},
    {{150, 0, 180, 20, 25, 135, 45, 155}, 50},
    {{170, 45, 180, 20, 25, 135, 45, 175}, 50},
    {{170, 45, 135, 20, 25, 180, 45, 175}, 50},
    {{150, 45, 135, 20, 25, 180, 45, 155}, 50},
    {{150, 45, 135, 20, 5, 180, 45, 155}, 50},
    {{150, 45, 135, 20, 25, 135, 45, 155}, 50}};

ServoPosition backwardSteps[] = {
    {{170, 0, 135, 20, 25, 135, 45, 175}, 50},
    {{150, 0, 135, 20, 25, 135, 45, 155}, 50},
    {{150, 0, 135, 0, 5, 135, 45, 155}, 50},
    {{150, 45, 135, 0, 5, 180, 0, 155}, 50},
    {{150, 45, 135, 20, 25, 180, 0, 155}, 50},
    {{170, 45, 135, 20, 25, 180, 45, 175}, 50},
    {{170, 45, 180, 20, 25, 135, 45, 175}, 50},
    {{150, 45, 180, 20, 25, 135, 45, 155}, 50},
    {{150, 45, 180, 0, 25, 135, 45, 155}, 50},
    {{150, 45, 135, 20, 25, 135, 45, 155}, 50}};

ServoPosition Turn_leftSteps[] = {
    {{170, 45, 135, 20, 25, 135, 45, 175}, 50},
    {{170, 90, 135, 20, 25, 135, 90, 175}, 50},
    {{150, 90, 135, 20, 25, 135, 90, 155}, 50},
    {{150, 90, 135, 0, 5, 135, 90, 155}, 50},
    {{150, 90, 180, 0, 5, 180, 90, 155}, 50},
    {{150, 90, 180, 20, 25, 180, 90, 155}, 50},
    {{150, 45, 135, 20, 25, 135, 45, 155}, 50}};

ServoPosition Turn_RightSteps[] = {
    {{170, 45, 135, 20, 25, 135, 45, 175}, 500},
    {{170, 90, 135, 20, 25, 135, 90, 175}, 500},
    {{150, 90, 135, 20, 25, 135, 90, 155}, 500},
    {{150, 90, 135, 0, 5, 135, 90, 155}, 500},
    {{150, 90, 180, 0, 5, 180, 90, 155}, 500},
    {{150, 90, 180, 20, 25, 180, 90, 140}, 500},
    //{{150, 10, 180, 20, 25, 180, 10, 155}, 500},
    //{{150, 90, 150, 20, 25, 150, 10, 155}, 500},
    {{150, 45, 135, 20, 25, 135, 45, 155}, 500}};

ServoPosition Dancing1[] = {
    {{85, 90, 90, 90, 95, 90, 90, 90}, 300},
    {{45, 90, 90, 90, 95, 90, 90, 90}, 300},
    {{85, 90, 90, 130, 95, 90, 90, 90}, 300},
    {{85, 90, 90, 90, 95, 90, 90, 50}, 300},
    {{85, 90, 90, 90, 135, 90, 90, 90}, 300},
    {{45, 90, 90, 90, 95, 90, 90, 90}, 300},
    {{85, 90, 90, 130, 95, 90, 90, 90}, 300},
    {{85, 90, 90, 90, 95, 90, 90, 50}, 300},
    {{85, 90, 90, 90, 135, 90, 90, 90}, 300},
    {{85, 90, 90, 90, 95, 90, 90, 90}, 300}};

ServoPosition Dancing2[] = {
    {{65,  45,  45, 110, 115, 135, 135,  70},300},
    {{110, 45, 45, 65, 115, 135, 135, 70}, 300},
    {{65, 45, 45, 110, 70, 135, 135, 115}, 300},
    {{110, 45, 45, 65, 115, 135, 135, 70}, 300},
    {{65, 45, 45, 110, 70, 135, 135, 115}, 300},
    {{110, 45, 45, 65, 115, 135, 135, 70}, 300},
    {{65, 45, 45, 110, 70, 135, 135, 115}, 300},
    {{110, 45, 45, 65, 115, 135, 135, 70}, 300},
    {{70, 45, 45, 105, 115, 135, 135, 70}, 300}};

ServoPosition Dancing3[] = {
    {{65,  45,  45, 110, 115, 135, 135,  70},300},
    {{105, 45, 135, 60, 75, 135, 45, 70}, 300},
    {{65, 45, 135, 110, 115, 135, 45, 70}, 300},
    {{105, 45, 135, 110, 75, 135, 45, 120}, 300},
    {{65, 45, 135, 110, 115, 135, 45, 70}, 300},
    {{105, 45, 135, 60, 75, 135, 45, 70}, 300},
    {{65, 45, 135, 110, 115, 135, 45, 70}, 300},
    {{105, 45, 135, 110, 75, 135, 45, 120}, 300},
    {{65, 45, 135, 110, 115, 135, 45, 70}, 300},
    {{65, 90, 180, 110, 115, 90, 0, 70}, 300}};

ServoPosition bot_sleep[] = {
    {{35, 90, 90, 145, 145, 90, 90, 35}, 400},
    {{30, 45, 135, 145, 150, 135, 45, 35}, 400},
    {{110, 45, 135, 55, 60, 135, 45, 115}, 1000}};

void servo_initialization()
{
    // 分配定时器
    ESP32PWM::allocateTimer(0);
    ESP32PWM::allocateTimer(1);

    // 为每个舵机设置频率并连接到对应的引脚
    for (int i = 0; i < SERVO_COUNT; ++i)
    {
        servos[i].setPeriodHertz(SERVO_FREQUENCY);
        servos[i].attach(servoPins[i], MIN_WIDTH, MAX_WIDTH);
    }
}
// 设置舵机位置函数，接受一个位置数组和一个延时时间
void setServoPositions(const int positions[], int delayTime)
{
    // 设置每个舵机的位置
    for (int i = 0; i < SERVO_COUNT; ++i)
    {
        servos[i].write(positions[i]);
        delay(35);
    }
    // 在设置完所有舵机的位置后进行延时
    delay(delayTime);
}
// 应用舵机位置函数
void applyServoPosition(const ServoPosition &position)
{
    // 调用 setServoPositions 函数设置舵机位置
    setServoPositions(position.positions, position.delayTime);
}
// 机器人运动函数，接受一个步态数组和步态数量
void robot_Movement(const ServoPosition steps[], int stepCount)
{
    // 依次应用每个步态
    for (int i = 0; i < stepCount; ++i)
    {
        applyServoPosition(steps[i]);
    }
}
// 机器人初始位置函数，设置机器人到初始位置
void robot_position()
{
    applyServoPosition(initialPos);
}

void robot_fuwei()
{
    applyServoPosition(fuwei);
}

void robot_Forward()
{
    robot_Movement(forwardSteps, sizeof(forwardSteps) / sizeof(forwardSteps[0]));
    // applyServoPosition(initialPos);
}

void robot_Backward()
{
    robot_Movement(backwardSteps, sizeof(backwardSteps) / sizeof(backwardSteps[0]));
    // applyServoPosition(initialPos);
}

void robot_Turn_left()
{
    robot_Movement(Turn_leftSteps, sizeof(Turn_leftSteps) / sizeof(Turn_leftSteps[0]));
    // applyServoPosition(initialPos);
}
void robot_Turn_Right()
{
    robot_Movement(Turn_RightSteps, sizeof(Turn_RightSteps) / sizeof(Turn_RightSteps[0]));
    // applyServoPosition(initialPos);
}

void robot_Dancing1()
{
    robot_Movement(Dancing1, sizeof(Dancing1) / sizeof(Dancing1[0]));
    // applyServoPosition(initialPos);
}
void robot_Dancing2()
{
    robot_Movement(Dancing2, sizeof(Dancing2) / sizeof(Dancing2[0]));
    // applyServoPosition(initialPos);
}
void robot_Dancing3()
{
    robot_Movement(Dancing3, sizeof(Dancing3) / sizeof(Dancing3[0]));
    // applyServoPosition(initialPos);
}
void robot_sleep()
{
    robot_Movement(bot_sleep, sizeof(bot_sleep) / sizeof(bot_sleep[0]));
    // applyServoPosition(initialPos);
}