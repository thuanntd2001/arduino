
const int trigPhai = 11;     // chân trig của HC-SR04
const int echoPhai = 12;     // chân echo của HC-SR04    
const int trigGiua = 9;     // chân trig của HC-SR04
const int echoGiua = 10;     // chân echo của HC-SR04   
const int trigTrai = 7;     // chân trig của HC-SR04
const int echoTrai = 8;     // chân echo của HC-SR04

const int pw=13

const byte LEFT = 1;
const byte RIGHT = 0;
const byte MID = -1;


int disTrai;           // biến lưu khoảng cách
int disGiua;           // biến lưu khoảng cách
int disPhai;           // biến lưu khoảng cách
int gap=150;
int danger=30;

int speed=255;




void doDistance(){
  unsigned long duration; // biến đo thời gian

    
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
    disTrai = int(duration/2/29.412);


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
    disGiua = int(duration/2/29.412);

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
    disPhai = int(duration/2/29.412);

}


void setup()
{
    Serial.begin(9600);     // giao tiếp Serial với baudrate 9600
    pinMode(trigTrai,OUTPUT);   // chân trig sẽ phát tín hiệu
    pinMode(trigGiua,OUTPUT);   // chân trig sẽ phát tín hiệu
    pinMode(trigPhai,OUTPUT);   // chân trig sẽ phát tín hiệu

    pinMode(echoTrai,INPUT);    // chân echo sẽ nhận tín hiệu
    pinMode(echoGiua,INPUT);    // chân echo sẽ nhận tín hiệu
    pinMode(echoPhai,INPUT);    // chân echo sẽ nhận tín hiệu


    pinMode(pw,OUTPUT);
    digitalWrite(pw,1);   

}
 void loop()
{
    doDistance();
    Serial.print("disTrai: ");
    Serial.println(disTrai);
    Serial.print("disGiua: ");
    Serial.println(disGiua);
    Serial.print("disPhai: ");
    Serial.println(disPhai);

}
