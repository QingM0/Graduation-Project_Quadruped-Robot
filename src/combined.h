#ifndef COMBINED_H
#define COMBINED_H

#include <ArduinoJson.h>
#include <Arduino.h>
#include <U8g2lib.h>
#include <WiFi.h>
#include <Adafruit_GFX.h>
#include <SoftwareSerial.h>
// #include <Adafruit_PWMServoDriver.h>
#include <ESP32Servo.h>
#include <Wire.h>
#include "AHT10.h"
#include "time.h"

// extern Servo servo1;
// extern Servo servo2;
// extern Servo servo3;
// extern Servo servo4;
// extern Servo servo5;
// extern Servo servo6;
// extern Servo servo7;
// extern Servo servo8;


void getHitokoto();
void getqweather();

void weather_display();
void UI_display_time();
void UI_display_weather();


void servo_initialization();
void Rbt_Init();
void move_forward();

String time_1();

#endif // COMBINED_H
