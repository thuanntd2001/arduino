#include <Servo.h> 

Servo servo;  
int Position = 0;  

void setup() 
{
 Serial.begin(9600);     // giao tiếp Serial với baudrate 9600

  servo.attach(10);   
}

void loop() 
{
  // rotates from 0 degrees to 180 degrees
  for(Position = 0; Position <= 180; Position += 1) 
  {
    servo.write(Position);
    delay(15);
  }
Serial.println("quay toi xong");
  // rotates from 180 degrees to 0 degrees
  for(Position = 180; Position>=0; Position-=1)
  {
    servo.write(Position);
    delay(15);
  }
  Serial.println("quay lui xong");

}