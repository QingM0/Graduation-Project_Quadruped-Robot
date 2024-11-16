#include "combined.h"

#define MAX_WIDTH 2500 // 舵机的最大宽度
#define MIN_WIDTH 500 // 舵机的最小宽度
#define SERVO_FREQUENCY 50 // 舵机的频率
#define SERVO_COUNT 8 // 舵机的数量

// 定义舵机数组和对应的引脚数组
Servo servos[SERVO_COUNT];
const int servoPins[SERVO_COUNT] = {32, 33, 25, 26, 17, 16, 4, 2};

// 定义舵机位置结构体，包含舵机位置数组和延时时间
struct ServoPosition
{
    int positions[SERVO_COUNT];
    int delayTime;
};

// 定义初始位置
ServoPosition initialPos = {{155, 45, 135, 15, 15, 135, 45, 155}, 50};

ServoPosition forwardSteps[] = {
    {{175, 45, 135, 15, 15, 135, 0, 175 }, 50},
    {{155, 45, 135, 15, 15, 135, 0, 155 }, 50},
    {{155, 45, 135, -5, -5, 135, 0, 155 }, 50},
    {{155, 0, 180, -5, -5, 135, 45, 155 }, 50},
    {{155, 0, 180, 15, 15, 135, 45, 155 }, 50},
    {{175, 45, 180, 15, 15, 135, 45, 175}, 50},
    {{175, 45, 135, 15, 15, 180, 45, 175}, 50},
    {{155, 45, 135, 15, 15, 180, 45, 155}, 50},
    {{155, 45, 135, 15, -5, 180, 45, 155}, 50},
    {{155, 45, 135, 15, 15, 135, 45, 155}, 50}};

ServoPosition backwardSteps[] = {
   { {175, 0, 135, 15, 15, 135, 45, 175 }, 50},
   { {195, 0, 135, 15, 15, 135, 45, 155 }, 50},
   { {195, 0, 135, -5, -5, 135, 45, 155 }, 50},
   { {195, 45, 135, -5, -5, 180, 0, 155 }, 50},
   { {195, 45, 135, 15, 15, 180, 0, 155 }, 50},
   { {215, 45, 135, 15, 15, 180, 45, 175}, 50},
   { {215, 45, 180, 15, 15, 135, 45, 175}, 50},
   { {235, 45, 180, 15, 15, 135, 45, 155}, 50},
   { {235, 45, 180, -5, 15, 135, 45, 155}, 50},
   { {235, 45, 135, 15, 15, 135, 45, 155}, 50}};

ServoPosition Move_leftSteps[] = {
   { {155, 45, 90, -5, -5, 135, 45, 155 }, 50},
   { {155, 45, 90, 15, 15, 135, 45, 155 }, 50},
   { {175, 45, 90, 15, 15, 135, 45, 175 }, 50},
   { {175, 90, 135, 15, 15, 90, 45, 175 }, 50},
   { {195, 90, 135, 15, 15, 90, 45, 155 }, 50},
   { {195, 90, 135, -5, -5, 135, 45, 155}, 50},
   { {195, 45, 135, -5, -5, 135, 90, 155}, 50},
   { {195, 45, 135, 15, 15, 135, 90, 155}, 50},
   { {195, 45, 135, 15, 15, 135, 90, 175}, 50},
   { {195, 45, 135, 15, 15, 135, 45, 155}, 50}};

ServoPosition Move_RightSteps[] = {
   { {155, 45, 135, -5, -5, 90, 45, 155}, 50},
   { {155, 45, 135, 15, 15, 90, 45, 155}, 50},
   { {175, 45, 135, 15, 15, 90, 45, 175}, 50},
   { {175, 45, 90, 15, 15, 135, 90, 175}, 50},
   { {155, 45, 90, 15, 15, 135, 90, 155}, 50},
   { {155, 45, 135, -5, -5, 135, 90, 155}, 50},
   { {155, 90, 135, -5, -5, 135, 45, 155}, 50},
   { {155, 90, 135, 15, 15, 135, 45, 155}, 50},
   { {175, 90, 135, 15, 15, 135, 45, 155}, 50},
   { {155, 45, 135, 15, 15, 135, 45, 155}, 50}}; // 舵机初始化函数，为每个舵机分配定时器并设置频率
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
        delay(10);
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

void robot_Forward()
{
    robot_Movement(forwardSteps, sizeof(forwardSteps) / sizeof(forwardSteps[0]));
    applyServoPosition(initialPos);
}

void robot_Backward()
{
    robot_Movement(backwardSteps, sizeof(backwardSteps) / sizeof(backwardSteps[0]));
    applyServoPosition(initialPos);
}

void robot_Left()
{
    robot_Movement(Move_leftSteps, sizeof(Move_leftSteps) / sizeof(Move_leftSteps[0]));
    applyServoPosition(initialPos);
}
void robot_Right()
{
    robot_Movement(Move_RightSteps, sizeof(Move_RightSteps) / sizeof(Move_RightSteps[0]));
    applyServoPosition(initialPos);
}