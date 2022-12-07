#include "MotorDriver.h"

MotorDriver m;
void setup() {
  // put your setup code here, to run once:

}

void loop() {
 m.motor(1,FORWARD,255);
      // m.motor(2,FORWARD,255);  
     //m.motor(3,BACKWARD,255);
      // m.motor(4,BACKWARD,255);  
}
