#include <Servo.h>

    const int trig = 13;     // chân trig của HC-SR04
    const int echo = 2;     // chân echo của HC-SR04
    const int led = 10;     // chân echo của HC-SR04
    const bool LEFT = 1;
    const bool RIGHT = 0;
    int const InitPos = 0;  
    int const EndPos = 120;
    int const MidPos = 50;
    int distance;           // biến lưu khoảng cách
    int disLeft;           // biến lưu khoảng cách
    int disRight;           // biến lưu khoảng cách
    int gap=300;
    Servo servo;  

    int pos = 0;   
    void setup()
    {
       
        pinMode(trig,OUTPUT);   // chân trig sẽ phát tín hiệu
        pinMode(echo,INPUT);    // chân echo sẽ nhận tín hiệu
        servo.attach(9);
        servo.write(MidPos);  

    }
     
    int doDistance(){
      unsigned int duration; // biến đo thời gian
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
      if (dir == LEFT){
      servo.write(InitPos);  
      delay(gap);
      distance  = doDistance();
      servo.write(MidPos);
      delay(gap);
              
      }else if (dir == RIGHT){
      servo.write(EndPos); 
      delay(gap);
             
      distance  = doDistance();
      servo.write(MidPos); 
      delay(gap);

      }
      return  distance;
    }
    void loop()
    {
        disLeft= scan(LEFT);
        disRight= scan(RIGHT);
        
        /* In kết quả ra Serial Monitor */
        if (disLeft<=15 ||disRight<=15) {
          
   
          digitalWrite(led,1);


         }

        else  {
          digitalWrite(led,0);
          }
      
    }