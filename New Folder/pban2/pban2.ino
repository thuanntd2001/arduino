#define SSID "KYV41"
#define PASSWORD "kamomechan"

char thingSpeakAddress[] = "api.thingspeak.com";
String writeAPIKey = "255XXW7UALLLYJBV";
const int updateThingSpeakInterval = 16 * 1000; // Time interval in milliseconds to update ThingSpeak (number of seconds * 1000 = interval)

// Variable Setup
long lastConnectionTime = 0;
boolean lastConnected = false;
int failedCounter = 0;

#include "uartWIFI.h"
WIFI wifi;

void setup()
{

wifi.begin();
bool b = wifi.Initialize(STA, SSID, PASSWORD);
if(!b)
{
DebugSerial.println("Init error");
}
delay(8000); //make sure the module can have enough time to get an IP address
String ipstring = wifi.showIP();
DebugSerial.println("My IP address:");
DebugSerial.println(ipstring); //show the ip address of module

String wifistring = wifi.showJAP();
DebugSerial.println(wifistring); //show the name of current wifi access port

}
void loop()
{

DebugSerial.println("thingspeak connect");

updateThingSpeak("field1=68687687687");
delay(30000);

}

void updateThingSpeak(String tsData)
{
if (wifi.newMux(1,thingSpeakAddress, 80))
{
wifi.Send("POST /update HTTP/1.1\n");
wifi.Send("Host: api.thingspeak.com\n");
wifi.Send("Connection: close\n");
wifi.Send("X-THINGSPEAKAPIKEY: "+writeAPIKey+"\n");
wifi.Send("Content-Type: application/x-www-form-urlencoded\n");
wifi.Send("Content-Length: ");
wifi.Send(String(tsData.length()));
wifi.Send("\n\n");

wifi.Send(tsData);

lastConnectionTime = millis();

Serial.println("Success");
wifi.closeMux();
}
else
{
failedCounter++;

Serial.println("Connection to ThingSpeak Failed ("+String(failedCounter, DEC)+")");

lastConnectionTime = millis();
}
}
