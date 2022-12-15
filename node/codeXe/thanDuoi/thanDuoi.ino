#include <Servo.h>
#include "MotorDriver.h"

/*011 tien 
110 lui 
101 trai
100 phai
010 dung
001 tulai*/

int pinC1=A0;
int pinC2=A4;
int pinC3=A5;
int c1=0;
int c2=0;
int c3=0;
int gap=300;
int speed = 255;
MotorDriver m;

void dung(MotorDriver m){
  m.motor(1,BRAKE,speed);
   m.motor(2,BRAKE,speed);  
   m.motor(3,BRAKE,speed);
   m.motor(4,BRAKE,speed); 
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


void setup()
{
 
    pinMode(pinC1,INPUT);    
    pinMode(pinC2,INPUT);    
    pinMode(pinC3,INPUT);    
    Serial.begin(9600);


}

 void loop()
{  
  c1=digitalRead(pinC1);
  c2=digitalRead(pinC2);
  c3=digitalRead(pinC3);
  Serial.print(c1);
  Serial.print(" ");
  Serial.print(c2);
  Serial.print(" ");
  Serial.print(c3);
  Serial.print("\n");
  
/*011 tien 
110 lui 
101 trai
100 phai
010 dung*/
  
  if(c1==0 && c2==1 && c3==1){tien(m);} 
 if(c1==1 && c2==1 && c3==0){lui(m);}
 if(c1==1 && c2==0 && c3==1){quayTrai(m);}
 if(c1==1 && c2==0 && c3==0){quayPhai(m);}
 if(c1==0 && c2==1 && c3==0){dung(m);}

}



