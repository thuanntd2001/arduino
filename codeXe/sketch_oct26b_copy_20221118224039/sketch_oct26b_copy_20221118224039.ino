#include <Servo.h>
#include "MotorDriver.h"
    const int trig = 13;     // chân trig của HC-SR04
    const int echo = 2;     // chân echo của HC-SR04
    const int led = 10;     // chân echo của HC-SR04
    const byte LEFT = 1;
    const byte RIGHT = 0;
    const byte MID = -1;

    int const InitPos = 0;  
    int const EndPos = 100;
    int const MidPos = 40;
    int distance;           // biến lưu khoảng cách
    int disLeft;           // biến lưu khoảng cách
    int disMid;           // biến lưu khoảng cách

    int disRight;           // biến lưu khoảng cách
    int gap=150;
    int danger=30;
    Servo servo;  
    MotorDriver m;
    int speed=255;
    int turn=255;
    int pos = 0;   
    int safe =15; 

 
int doDistance(){
  unsigned long duration; // biến đo thời gian
    int distance;           // biến lưu khoảng cách
    
    /* Phát xung từ chân trig */
    digitalWrite(trig,0);   // tắt chân trig
    delayMicroseconds(2);
    digitalWrite(trig,1);   // phát xung từ chân trig
    delayMicroseconds(5);   // xung có độ dài 5 microSeconds
    digitalWrite(trig,0);   // tắt chân trig
    
    /* Tính toán thời gian */
    // Đo độ rộng xung HIGH ở chân echo. 
    duration = pulseIn(echo,HIGH);  
    // Tính khoảng cách đến vật.
    distance = int(duration/2/29.412);
    
    /* In kết quả ra Serial Monitor */
    return distance;

}

int scan(bool dir){
  int distance;
  if (dir == RIGHT){
  servo.write(InitPos);  
  delay(gap);
  distance  = doDistance();
   
  }
  else if (dir == LEFT){
  servo.write(EndPos); 
  delay(gap);
  distance  = doDistance();
  }
  else if (dir == MID){
  servo.write(MidPos);
  delay(gap);

  distance  = doDistance();
  }
  return  distance;
}
void dung(MotorDriver m){
  m.motor(1,RELEASE,speed);
   m.motor(2,RELEASE,speed);  
   m.motor(3,RELEASE,speed);
   m.motor(4,RELEASE,speed); 
}

void tien(MotorDriver m){
   m.motor(4,BACKWARD,speed);
   m.motor(3,BACKWARD,speed);  
   m.motor(2,BACKWARD,speed);
   m.motor(1,BACKWARD,speed);
 
 
}
void lui(MotorDriver m){
   m.motor(1,FORWARD,speed);
   m.motor(2,FORWARD,speed);  
   m.motor(3,FORWARD,speed);
   m.motor(4,FORWARD,speed);  
   

}
void quayPhai(MotorDriver m){
   m.motor(1,FORWARD,speed);
   m.motor(2,FORWARD,speed);  
   m.motor(3,BACKWARD,speed);
   m.motor(4,BACKWARD,speed);  

}
    
void quayTrai(MotorDriver m){
   m.motor(1,BACKWARD,speed);
   m.motor(2,BACKWARD,speed);  
   m.motor(3,FORWARD,speed);
   m.motor(4,FORWARD,speed);  
    delay(gap);
 
}   

int fullScan(){
    disLeft= scan(LEFT);    
  if(disLeft<safe) {return disLeft;}    
    delay(gap);
    disRight= scan(RIGHT);
    if(disRight<safe) {return disRight;}        

    delay(gap);

    disMid= scan(MID);
    if(disMid<safe) {return disMid;}     


    
    if(disLeft>disMid and disRight>disMid) return disMid;
    if(disLeft<disRight and disLeft<disMid) return disLeft;
    if(disLeft>disRight and disRight<disMid) return disRight;
    else return 0;


}
void setup()
{
    Serial.begin(9600);     // giao tiếp Serial với baudrate 9600
    pinMode(trig,OUTPUT);   // chân trig sẽ phát tín hiệu
    pinMode(echo,INPUT);    // chân echo sẽ nhận tín hiệu
    servo.attach(9);
    servo.write(MidPos);  
    pinMode(led,OUTPUT);
    tien(m);
}
 void loop()
{
    // distance=fullScan();

    
    // if (distance<=safe) {
    //   digitalWrite(led,1);

    // //   dung(m);
    // // delay(gap*3);
    // // lui(m);
    // //   //delay(5000);
      
    // //   //lui(m);
     
      
    // //   if(disRight>disLeft>danger){
    // //     quayPhai(m);
    // //   }
    // //   else if(disLeft>disRight>danger){
    // //     quayTrai(m);
    // //   }   
    // //   else{
    // //     quayPhai(m);
    // //     quayPhai(m);
    // //   }       
      


    //  }

    // else  {
    //       tien(m); 
    //       //delay(gap);
    //       digitalWrite(led,0);

    //   }
//   tien(m);

//   delay(5000);
// lui(m);

 //quayTrai(m);
// quayTrai(m);
 //delay(10000);

// quayPhai(m);
// quayPhai(m);
// delay(4000);

}
