

const int trigTrai = A5;     // chân trig của HC-SR04
const int echoTrai = A4;     // chân echo của HC-SR04
const int trigGiua = A3;     // chân trig của HC-SR04
const int echoGiua = A2;     // chân echo của HC-SR04
const int trigPhai = A1;     // chân trig của HC-SR04
const int echoPhai = A0;     // chân echo của HC-SR04
int pw3=13;
int pw2=8;
int pw1=2;

int gap=100; 
int turnGap=360; 
 
 const char* ssid = "KYV41";
 const char* password =  "kamomechan";

// const char* ssid = "NOKIA";
// const char* password =  "123456789";


int doDistanceTrai(){
      unsigned int duration; // biến đo thời gian
        int distance;           // biến lưu khoảng cách
        
        /* Phát xung từ chân trig */
        digitalWrite(trigTrai,0);   // tắt chân trig
        delayMicroseconds(2);
        digitalWrite(trigTrai,1);   // phát xung từ chân trig
        delayMicroseconds(5);   // xung có độ dài 5 microSeconds
        digitalWrite(trigTrai,0);   // tắt chân trig
        
        /* Tính toán thời gian */
        // Đo độ rộng xung HIGH ở chân echo. 
        duration = pulseIn(echoTrai,HIGH);  
        // Tính khoảng cách đến vật.
        distance = int(duration/2/29.412);
        
        /* In kết quả ra Serial Monitor */
        return distance;

    }
int doDistanceGiua(){
      unsigned int duration; // biến đo thời gian
        int distance;           // biến lưu khoảng cách
        
        /* Phát xung từ chân trig */
        digitalWrite(trigGiua,0);   // tắt chân trig
        delayMicroseconds(2);
        digitalWrite(trigGiua,1);   // phát xung từ chân trig
        delayMicroseconds(5);   // xung có độ dài 5 microSeconds
        digitalWrite(trigGiua,0);   // tắt chân trig
        
        /* Tính toán thời gian */
        // Đo độ rộng xung HIGH ở chân echo. 
        duration = pulseIn(echoGiua,HIGH);  
        // Tính khoảng cách đến vật.
        distance = int(duration/2/29.412);
        
        /* In kết quả ra Serial Monitor */
        return distance;

    }
int doDistancePhai(){
      unsigned int duration; // biến đo thời gian
        int distance;           // biến lưu khoảng cách
        
        /* Phát xung từ chân trig */
        digitalWrite(trigPhai,0);   // tắt chân trig
        delayMicroseconds(2);
        digitalWrite(trigPhai,1);   // phát xung từ chân trig
        delayMicroseconds(5);   // xung có độ dài 5 microSeconds
        digitalWrite(trigPhai,0);   // tắt chân trig
        
        /* Tính toán thời gian */
        // Đo độ rộng xung HIGH ở chân echo. 
        duration = pulseIn(echoPhai,HIGH);  
        // Tính khoảng cách đến vật.
        distance = int(duration/2/29.412);
        
        /* In kết quả ra Serial Monitor */
        return distance;

    }


#include <SoftwareSerial.h>

SoftwareSerial swSer(0, 1, false, 128); //Define hardware connections

 
void setup() {

    pinMode(trigTrai,OUTPUT);   // chân trig sẽ phát tín hiệu
    pinMode(trigGiua,OUTPUT);   // chân trig sẽ phát tín hiệu
    pinMode(trigPhai,OUTPUT);   // chân trig sẽ phát tín hiệu
    pinMode(echoTrai,INPUT);    // chân echo sẽ nhận tín hiệu
    pinMode(echoPhai,INPUT);    // chân echo sẽ nhận tín hiệu
    pinMode(echoGiua,INPUT);    // chân echo sẽ nhận tín hiệu
    pinMode(pw1,OUTPUT);   // chân trig sẽ phát tín hiệu
    pinMode(pw2,OUTPUT);   // chân trig sẽ phát tín hiệu
    pinMode(pw3,OUTPUT);   // chân trig sẽ phát tín hiệu

    Serial.begin(9600);
    swSer.begin(9600);
    digitalWrite(pw1,1);
    digitalWrite(pw2,1);
    digitalWrite(pw3,1);

}
 
void loop() {
 
    int trai= doDistanceTrai();
    int giua= doDistanceGiua();
    int phai= doDistancePhai();
    Serial.print("trai");
      Serial.println(trai);
      Serial.print("giua");
      Serial.println(giua);
      Serial.print("phai");
      Serial.println(phai);

      delay(gap);
 
}
 
