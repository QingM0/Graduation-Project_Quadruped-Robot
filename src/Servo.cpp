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

// 定义初始位置
ServoPosition initialPos = {{150, 45, 135, 20, 20, 135, 45, 150}, 50};

ServoPosition forwardSteps[] = {
    {{170, 45, 135, 20, 20, 135, 0, 170}, 50},
    {{150, 45, 135, 20, 20, 135, 0, 150}, 50},
    {{150, 45, 135, 0, 0, 135, 0, 150}, 50},
    {{150, 0, 180, 0, 0, 135, 45, 150}, 50},
    {{150, 0, 180, 20, 20, 135, 45, 150}, 50},
    {{170, 45, 180, 20, 20, 135, 45, 170}, 50},
    {{170, 45, 135, 20, 20, 180, 45, 170}, 50},
    {{150, 45, 135, 20, 20, 180, 45, 150}, 50},
    {{150, 45, 135, 20, 0, 180, 45, 150}, 50},
    {{150, 45, 135, 20, 20, 135, 45, 150}, 50}};

ServoPosition backwardSteps[] = {
    {{170, 0, 135, 20, 20, 135, 45, 170}, 50},
    {{150, 0, 135, 20, 20, 135, 45, 150}, 50},
    {{150, 0, 135, 0, 0, 135, 45, 150}, 50},
    {{150, 45, 135, 0, 0, 180, 0, 150}, 50},
    {{150, 45, 135, 20, 20, 180, 0, 150}, 50},
    {{170, 45, 135, 20, 20, 180, 45, 170}, 50},
    {{170, 45, 180, 20, 20, 135, 45, 170}, 50},
    {{150, 45, 180, 20, 20, 135, 45, 150}, 50},
    {{150, 45, 180, 0, 20, 135, 45, 150}, 50},
    {{150, 45, 135, 20, 20, 135, 45, 150}, 50}};

ServoPosition Move_leftSteps[] = {
    {{150, 45, 90, 0, 0, 135, 45, 150}, 50},
    {{150, 45, 90, 20, 20, 135, 45, 150}, 50},
    {{170, 45, 90, 20, 20, 135, 45, 170}, 50},
    {{170, 90, 135, 20, 20, 90, 45, 170}, 50},
    {{150, 90, 135, 20, 20, 90, 45, 150}, 50},
    {{150, 90, 135, 0, 0, 135, 45, 150}, 50},
    {{150, 45, 135, 0, 0, 135, 90, 150}, 50},
    {{150, 45, 135, 20, 20, 135, 90, 150}, 50},
    {{150, 45, 135, 20, 20, 135, 90, 170}, 50},
    {{150, 45, 135, 20, 20, 135, 45, 150}, 50}};

ServoPosition Move_RightSteps[] = {
    {{150, 45, 135, 0, 0, 90, 45, 150}, 50},
    {{150, 45, 135, 20, 20, 90, 45, 150}, 50},
    {{170, 45, 135, 20, 20, 90, 45, 170}, 50},
    {{170, 45, 90, 20, 20, 135, 90, 170}, 50},
    {{150, 45, 90, 20, 20, 135, 90, 150}, 50},
    {{150, 45, 135, 0, 0, 135, 90, 150}, 50},
    {{150, 90, 135, 0, 0, 135, 45, 150}, 50},
    {{150, 90, 135, 20, 20, 135, 45, 150}, 50},
    {{170, 90, 135, 20, 20, 135, 45, 150}, 50},
    {{150, 45, 135, 20, 20, 135, 45, 150}, 50}}; // 舵机初始化函数，为每个舵机分配定时器并设置频率

ServoPosition Turn_leftSteps[] = {
    {{170, 45, 135, 20, 20, 135, 45, 170}, 50},
    {{170, 90, 135, 20, 20, 135, 90, 170}, 50},
    {{150, 90, 135, 20, 20, 135, 90, 150}, 50},
    {{150, 90, 135, 0, 0, 135, 90, 150}, 50},
    {{150, 90, 180, 0, 0, 180, 90, 150}, 50},
    {{150, 90, 180, 20, 20, 180, 90, 150}, 50},
    {{150, 45, 135, 20, 20, 135, 45, 150}, 50}};
ServoPosition Turn_RightSteps[] = {
    {{150, 45, 135, 0, 0, 135, 45, 150}, 30},
    {{150, 45, 90, 0, 0, 90, 45, 150}, 30},
    {{150, 45, 90, 20, 20, 90, 45, 150}, 30},
    {{170, 45, 90, 20, 20, 90, 45, 170}, 30},
    {{170, 0, 90, 20, 20, 90, 0, 170}, 30},
    {{150, 0, 90, 20, 20, 90, 0, 150}, 30},
    {{150, 45, 135, 20, 20, 135, 45, 150}, 30}};
ServoPosition Push_upSteps[] = {
    {{180, 45, 135, -10, -10, 135, 45, 180}, 200},
    {{150, 45, 135, 20, 20, 135, 45, 150}, 250},
    {{180, 45, 135, -10, -10, 135, 45, 180}, 300},
    {{150, 45, 135, 20, 20, 135, 45, 150}, 350},
    {{180, 45, 135, -10, -10, 135, 45, 180}, 750},
    {{150, 45, 135, 20, 20, 135, 45, 150}, 900},
    {{215, 45, 135, -45, -45, 135, 45, 215}, 100},
    {{150, 45, 135, -45, -30, 135, 45, 215}, 250},
    {{150, 45, 135, -45, 20, 135, 45, 215}, 250},
    {{150, 45, 135, 20, 20, 135, 45, 150}, 250}};
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
void robot_Turn_left()
{
    robot_Movement(Turn_leftSteps, sizeof(Turn_leftSteps) / sizeof(Turn_leftSteps[0]));
    applyServoPosition(initialPos);
}
void robot_Turn_Right()
{
    robot_Movement(Turn_RightSteps, sizeof(Turn_RightSteps) / sizeof(Turn_RightSteps[0]));
    applyServoPosition(initialPos);
}
void robot_Push_up()
{
    robot_Movement(Push_upSteps, sizeof(Push_upSteps) / sizeof(Push_upSteps[0]));
    // applyServoPosition(initialPos);
}
