
String ssid     = "KYV41";  // SSID to connect to
String password = "kamomechan"; // Our virtual wifi has no password 
String host     = "api.thingspeak.com"; // Open Weather Map API
const int httpPort   = 80;
String url     = "/update?api_key=255XXW7UALLLYJBV&field1=";
//arduino+sensor
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

int setupESP8266(void) {
  // Start our ESP8266 Serial Communication
  Serial.begin(115200);   // Serial connection over USB to computer
  Serial.println("AT");   // Serial connection on Tx / Rx port to ESP8266
  delay(10);        // Wait a little for the ESP to respond
  if (!Serial.find("OK")) return 1;
    
  // Connect to 123D Circuits Simulator Wifi
  Serial.println("AT+CWJAP=\"" + ssid + "\",\"" + password + "\"");
  delay(10);        // Wait a little for the ESP to respond
  if (!Serial.find("OK")) return 2;
  
  // Open TCP connection to the host:
  Serial.println("AT+CIPSTART=\"TCP\",\"" + host + "\"," + httpPort);
  delay(50);        // Wait a little for the ESP to respond
  if (!Serial.find("OK")) return 3;
  
  return 0;
}
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

void anydata(void) {
  
  //int temp = map(analogRead(A0),20,358,-40,125);
    temp=doDistance();
  
  // Construct our HTTP call
  String httpPacket = "GET " + url + String(temp) + " HTTP/1.1\r\nHost: " + host + "\r\n\r\n";
  int length = httpPacket.length();
  
  // Send our message length
  Serial.print("AT+CIPSEND=");
  Serial.println(length);
  delay(10); // Wait a little for the ESP to respond if (!Serial.find(">")) return -1;

  // Send our http request
  Serial.print(httpPacket);
  delay(10); // Wait a little for the ESP to respond
  if (!Serial.find("SEND OK\r\n")) return;
  
  
}


void setup() {
  
  setupESP8266();
               
}

void loop() {
  
 anydata();
  
  delay(5000);
}
