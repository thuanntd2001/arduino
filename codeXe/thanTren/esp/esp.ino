#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

int pinC1=1;
int pinC2=2;
int pinC3=3;
 
ESP8266WebServer server(80);
 
const char* ssid = "KYV41";
const char* password =  "kamomechan";
String command;
const char html[] = R"=====(
<!DOCTYPE html>
<html>
<head>
<meta name="viewport" content="width=device-width, initial-scale=1">
</head>
<style>

</style>
<body>
<form action="http://192.168.43.111/body" method="post" style=" color:blue;text-align:center"> <input type="hidden" name="command" value="tien"> <button style="font-size: 40"> tien</button></form><form action="http://192.168.43.111/body" method="post" style="color:blue;text-align:left; margin=25%"> <input type="hidden" name="command" value="trai"> <button style="font-size: 40"> trai</button></form><form action="http://192.168.43.111/body" method="post" style="color:blue;text-align:right"> <input type="hidden" name="command" value="phai"> <button style="font-size: 40"> phai</button></form><form action="http://192.168.43.111/body" method="post" style="color:blue;text-align:center"> <input type="hidden" name="command" value="lui"> <button style="font-size: 40"> lui</button></form><br><form action="http://192.168.43.111/body" method="post" style="color:blue;text-align:center"> <input type="hidden" name="command" value="dung"> <button style="font-size: 40"> dung</button></form><form action="http://192.168.43.111/body" method="post" style="color:blue;text-align:left"> <input type="hidden" name="command" value="quayTrai"> <button style="font-size: 40"> quayTrai</button></form><form action="http://192.168.43.111/body" method="post" style="color:blue;text-align:right"> <input type="hidden" name="command" value="quayPhai"> <button style="font-size: 40"> quayPhai</button></form>
</body>
</html>
)=====";
void handleBody() { //Handler for the body path
      

      if (server.hasArg("plain")== false){ //Check if body received
            char strRep[2000];
            strcat(strRep, html);
            server.send(200, "text/html", strRep);
            return;
 
      }
           String message = "Body received:\n";
             command=server.arg("plain");
             message += server.arg("plain");
             message += "\n";
 
      server.send(200, "text/html", message+html);
      Serial.println(message);
}
void setup() {
    pinMode(pinC1,OUTPUT);    
    pinMode(pinC2,OUTPUT);    
    pinMode(pinC3,OUTPUT);    

    Serial.begin(115200);
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
 
}
 
void loop() {
 
    server.handleClient(); //Handling of incoming requests
    if(command=="tien"){
        digitalWrite(pinC1,HIGHT);
        digitalWrite(pinC2,HIGHT);
        digitalWrite(pinC3,HIGHT);
    }
     if(command=="lui"){
            digitalWrite(pinC1,HIGHT);
            digitalWrite(pinC2,HIGHT);
            digitalWrite(pinC3,LOW);
        }
     if(command=="trai"){
            digitalWrite(pinC1,HIGHT);
            digitalWrite(pinC2,LOW);
            digitalWrite(pinC3,HIGHT);
        }
     if(command=="phai"){
            digitalWrite(pinC1,HIGHT);
            digitalWrite(pinC2,LOW);
            digitalWrite(pinC3,LOW);
        }
     if(command=="quayTrai"){
            digitalWrite(pinC1,LOW);
            digitalWrite(pinC2,HIGHT);
            digitalWrite(pinC3,HIGHT);
        }
     if(command=="quayPhai"){
            digitalWrite(pinC1,LOW);
            digitalWrite(pinC2,HIGHT);
            digitalWrite(pinC3,LOW);
        }
     if(command=="dung"){
            digitalWrite(pinC1,LOW);
            digitalWrite(pinC2,LOW);
            digitalWrite(pinC3,LOW);
        }

 
}
 
