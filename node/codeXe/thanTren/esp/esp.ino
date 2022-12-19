#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ArduinoJson.h>

int pinC1=14;
int pinC2=12;
int pinC3=13;


int pinTrai=4;
int pinGiua=5;
int pinPhai=16;

int gap=10; 
int turnGap=360; 
int cirGap=40;
int trai=-2;
int phai=-2;
int giua=-2;

DynamicJsonDocument doc(1024);

ESP8266WebServer server(80);
 
 const char* ssid = "KYV41";
 const char* password =  "kamomechan";

// const char* ssid = "NOKIA";
// const char* password =  "123456789";

String command="";
int random0;
const char html[] = R"=====(
<form action="http://192.168.43.242/body" method="post" style=" color:blue;text-align:center"> <input type="hidden" name="command" value="tien"> <button style="font-size: 40"> tien</button></form><form action="http://192.168.43.242/body" method="post" style="color:blue;text-align:left; margin=25%"> <input type="hidden" name="command" value="trai"> <button style="font-size: 40"> trai</button></form><form action="http://192.168.43.242/body" method="post" style="color:blue;text-align:right"> <input type="hidden" name="command" value="phai"> <button style="font-size: 40"> phai</button></form><form action="http://192.168.43.242/body" method="post" style="color:blue;text-align:center"> <input type="hidden" name="command" value="lui"> <button style="font-size: 40"> lui</button></form><br><form action="http://192.168.43.242/body" method="post" style="color:blue;text-align:center"> <input type="hidden" name="command" value="dung"> <button style="font-size: 40"> dung</button></form><form action="http://192.168.43.242/body" method="post" style="color:blue;text-align:left"> <input type="hidden" name="command" value="quayTrai"> <button style="font-size: 40"> quayTrai</button></form><form action="http://192.168.43.242/body" method="post" style="color:blue;text-align:right"> <input type="hidden" name="command" value="quayPhai"> <button style="font-size: 40"> quayPhai</button></form><form action="http://192.168.43.242/body" method="post" style="color:blue;text-align:right"> <input type="hidden" name="command" value="tulai"> <button style="font-size: 40"> tulai</button></form>
)=====";
void handleBody() { //Handler for the body path
     trai= digitalRead(pinTrai); // 1 ok 0 co vat can
  phai= digitalRead(pinPhai);
  giua= digitalRead(pinGiua);

      if (server.hasArg("plain")== false){ //Check if body received
            char strRep[2000];
            strcat(strRep, html);
            server.send(200, "text/html", strRep);
            return;
 
      }
  //     // Sending the request
  //   doc["type"] = "request";
  //   boolean messageReady = false;
  //   serializeJson(doc,Serial);
  //   while(messageReady == false) { // blocking but that's ok
  //   if(Serial.available()) {
  //     message1 = Serial.readString();
  //     messageReady = true;
  //   }
  // }
  //          // Attempt to deserialize the JSON-formatted message
  //   DeserializationError error = deserializeJson(doc,message1);
  //   if(error) {
  //     Serial.print(F("deserializeJson() failed: "));
  //     Serial.println(error.c_str());
      
  //   }
  //   else{ 
  //     trai = doc["trai"];
  //   phai = doc["phai"];
  //   giua = doc["giua"];  

  //   }
   
    String message = "Lenh da nhan:\n";
             command=server.arg("plain");
             message += server.arg("plain");
             message += "\n";
              message += "trai: ";
              message += trai;
              message += "giua: ";
              message += giua;
              message += "phai: ";
              message += phai;

 
      server.send(200, "text/html", message+html);
      Serial.println(message);
      }
           


/*011 tien 
110 lui 
101 quaytrai
100 quayphai
010 dung
001 tulai*/


void tien(){
        digitalWrite(pinC1,LOW);
        digitalWrite(pinC2,HIGH);
        digitalWrite(pinC3,HIGH);
    }
void lui(){
        digitalWrite(pinC1,HIGH);
        digitalWrite(pinC2,HIGH);
        digitalWrite(pinC3,LOW);
    }
void quayTrai(){
        digitalWrite(pinC1,HIGH);
        digitalWrite(pinC2,LOW);
        digitalWrite(pinC3,HIGH);
    }
void quayPhai(){
        digitalWrite(pinC1,HIGH);
        digitalWrite(pinC2,LOW);
        digitalWrite(pinC3,LOW);
    }

void dung(){
        digitalWrite(pinC1,LOW);
        digitalWrite(pinC2,HIGH);
        digitalWrite(pinC3,LOW);
    }

void reTrai(){
        quayTrai();
        delay(turnGap);
command="command=dung" ;   }
void rePhai(){
        quayPhai();
        delay(turnGap);
command="command=dung";    }

void quayPhaiThat(){
        quayPhai();
        delay(cirGap);
        dung();
        delay(cirGap);
    }
void quayTraiThat(){
        quayTrai();
        delay(cirGap);
        dung();
        delay(cirGap);
    }
void tulai(){ 
  

 trai= digitalRead(pinTrai); // 1 ok 0 co vat can
  phai= digitalRead(pinPhai);
  giua= digitalRead(pinGiua);

        if(trai>0 && giua>0 && phai>0){
          tien();
              command="command=tulai";

        }
                      
        else if(trai > 0)    {

              reTrai();
              command="command=tulai";
              }
        else if(phai > 0)    {
              rePhai();
              command="command=tulai";

              }
        else {
          random0=random(2400);
          if (random0%2==0)
          quayTrai();
          else
          quayPhai();
          delay(random0);
          reTrai();

              command="command=tulai";

                    
        }          
 
}         


 
void setup() {
    pinMode(pinC1,OUTPUT);    
    pinMode(pinC2,OUTPUT);    
    pinMode(pinC3,OUTPUT);    

    pinMode(pinTrai,INPUT);    
    pinMode(pinPhai,INPUT);    
    pinMode(pinGiua,INPUT);   

    Serial.begin(9600);
    WiFi.begin(ssid, password);  //Connect to the WiFi network
 
    while (WiFi.status() != WL_CONNECTED) {  //Wait for connection
 
        delay(500);
        Serial.println("Waiting to connect...");
 
    }
     Serial.print(html);

    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());  //Print the local IP
 
    server.on("/body", handleBody); //Associate the handler function to the path
 
    server.begin(); //Start the server
    Serial.println("Server listening");
 dung();
}
 
void loop() {

    server.handleClient(); //Handling of incoming requests
     
    
    if(command=="command=tien"){
      Serial.println("tien");
       tien();
    }
     if(command=="command=lui"){
           Serial.println("lui");
           lui();
        }
     if(command=="command=trai"){

      Serial.println("trai");
           reTrai();
        }
     if(command=="command=phai"){
      Serial.println("phai");
        rePhai();
        }
     if(command=="command=quayTrai"){
      Serial.println("quayTrai");

       quayTraiThat();
        }
     if(command=="command=quayPhai"){
      Serial.println("quayPhai");

          quayPhaiThat();
        }
     if(command=="command=dung"){
      Serial.println("dung");

         dung();
        }
    if(command=="command=tulai"){
      Serial.println("tulai");

         tulai();
        }

      
}
 
