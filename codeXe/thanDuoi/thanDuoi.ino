#include <Servo.h>
#include "MotorDriver.h"


int pinC1=A0;
int pinC2=A4;
int pinC3=A5;
int c1;
int c2;
int c3;
int gap=300;

void dung(MotorDriver m){
  m.motor(1,RELEASE,speed);
   m.motor(2,RELEASE,speed);  
   m.motor(3,RELEASE,speed);
   m.motor(4,RELEASE,speed); 
}

void lui(MotorDriver m){
   m.motor(4,BACKWARD,speed);
   m.motor(3,BACKWARD,speed);  
   m.motor(2,BACKWARD,speed);
   m.motor(1,BACKWARD,speed);
 
 
}
void tien(MotorDriver m){
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

}   

void reTrai(MotorDriver m){
    quayTrai( m);
    delay(gap);
    tien(m);
}
void rePhai(MotorDriver m){
    quayPhai( m);
    delay(gap);
    tien(m);
}
void setup()
{
 
    pinMode(pinC1,INPUT);    
    pinMode(pinC2,INPUT);    
    pinMode(pinC3,INPUT);    


}

 void loop()
{  
  c1=digitalRead(pinC1);
  c2=digitalRead(pinC2);
  c3=digitalRead(pinC3);
  if(c1==HIGHT){//tien lui re
    if (c2==HIGHT){//tien lui
        if (c3==HIGHT){
            tien(m);
        }else{
            lui(m);
        }

    }else {//re
        if (c3==HIGHT){
            reTrai(m);
        }else{
            rePhai(m);
        }
    }

  }
  else{//dung quay
    if (c2==HIGHT){//quay
            if (c3==HIGHT){
                quayTrai(m);
            }else{
                quayPhai(m);
            }

        }else {//dung
            if (c3==HIGHT){
                //reTrai(m);
            }else{
                dung(m);
            }
        }
    }  

}



