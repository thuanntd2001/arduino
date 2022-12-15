/*
    This sketch establishes a TCP connection to a "quote of the day" service.
    It sends a "hello" message, and then prints received data.
*/

#include <ESP8266WiFi.h>

#ifndef STASSID
#define STASSID "KYV41"
#define STAPSK  "kamomechan"
#endif

const char* ssid     = STASSID;
const char* password = STAPSK;

const char* host = "api.thingspeak.com";
const uint16_t port = 80;

String API = "255XXW7UALLLYJBV";
String field = "field1";
int valSensor;
const int trig = 1;     // chân trig của HC-SR04
const int echo = 4;     // chân echo của HC-SR04
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
void setup() {
  Serial.begin(115200);

  // We start by connecting to a WiFi network

  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  /* Explicitly set the ESP8266 to be a WiFi-client, otherwise, it by default,
     would try to act as both a client and an access-point and could cause
     network-issues with your other WiFi-devices on your WiFi-network. */
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  static bool wait = false;

  Serial.print("connecting to ");
  Serial.print(host);
  Serial.print(':');
  Serial.println(port);

  // Use WiFiClient class to create TCP connections
  WiFiClient client;
  if (!client.connect(host, port)) {
    Serial.println("connection failed");
    delay(5000);
    return;
  }

  // This will send a string to the server
  Serial.println("sending data to server");
  valSensor = doDistance(); //lay khoang cach tu cam bien
 // String urlUp = "GET /update?api_key="+ API +"&"+ field +"="+String(valSensor);
  // Serial.println(valSensor);
  // Serial.print(urlUp);
  // Serial.print(",");
  // Serial.println(urlUp.length());
    Serial.println("valSensor la: ");
   Serial.println(valSensor);


  if (client.connected()) {
      String data_to_send = API;
      data_to_send += "&field1="; 
      data_to_send += valSensor;
      // data_to_send += "&field2=";
      // data_to_send += t;
      data_to_send += "\r\n\r\n";

      client.print("POST /update HTTP/1.1\n");
      client.print("Host: api.thingspeak.com\n");
      client.print("Connection: close\n");
      client.print("X-THINGSPEAKAPIKEY: " + API + "\n");
      client.print("Content-Type: application/x-www-form-urlencoded\n");
      client.print("Content-Length: ");
      client.print(data_to_send.length());
      client.print("\n\n");
      client.print(data_to_send);
         
  }

  // wait for data to be available
  unsigned long timeout = millis();
  while (client.available() == 0) {
    if (millis() - timeout > 5000) {
      Serial.println(">>> Client Timeout !");
      client.stop();
      delay(60000);
      return;
    }
  }

  // Read all the lines of the reply from server and print them to Serial
  Serial.println("receiving from remote server");
  // not testing 'client.connected()' since we do not need to send data here
  while (client.available()) {
    char ch = static_cast<char>(client.read());
    Serial.print(ch);
  }

  // Close the connection
  Serial.println();
  Serial.println("closing connection");
  client.stop();

  if (wait) {
    delay(3000); // execute once every 30s, don't flood remote service
  }
  wait = true;
}
