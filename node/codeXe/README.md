#include <Servo.h>
#include "MotorDriver.h"
    const int trig = 13;     // chân trig của HC-SR04
    const int echo = 2;     // chân echo của HC-SR04
    const int led = 13;     // chân echo của HC-SR04
    const byte LEFT = 1;
    const byte RIGHT = 0;
    const byte MID = -1;

    int const InitPos = 0;  
    int const EndPos = 120;
    int const MidPos = 50;
    int distance;           // biến lưu khoảng cách
    int disLeft;           // biến lưu khoảng cách
    int disMid;           // biến lưu khoảng cách

    int disRight;           // biến lưu khoảng cách
    int gap=150;
    int danger=30;
    Servo servo;  
    MotorDriver m;
    int speed=200;
    int turn=255;
    int pos = 0;   
    int safe =20; 
    void setup()
    {
        Serial.begin(9600);     // giao tiếp Serial với baudrate 9600
        pinMode(trig,OUTPUT);   // chân trig sẽ phát tín hiệu
        pinMode(echo,INPUT);    // chân echo sẽ nhận tín hiệu
        servo.attach(9);
        servo.write(MidPos);  

    }