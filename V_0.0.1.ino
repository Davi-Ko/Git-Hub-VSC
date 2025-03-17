#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>

//Wifi generated by the ESP-01
const char* ssidAP = "Relay_1";
const char* passwordAP = "abc12345";

//IP of this relay
IPAddress local_ip(192, 168, 4, 3);
IPAddress gateway(192, 168, 4, 1);
IPAddress subnet(255, 255, 255, 0); 

//Configuration of the Wifi from the other ESP-01
const char* ssidClient = "Relay_2";
const char* passwordClient = "abc12345";
const char* serverIP = "192.168.4.2";

//Creating the WebServer
ESP8266WebServer server(80);

//Defining the pin of the ESP-01 that will command the relay
const int relayPin = 0;

//Relay Configuration
void setup(){
    Serial.begin(115200);

    pinMode(relayPin, OUTPUT);
    digitalWrite(relayPin, HIGH);

    //Configures this relay as Access Point
    WiFi.softAP(ssidAP, passwordAP);
    WiFi.softAPConfig(local_ip, gateway, subnet);

    //Makes this relay to connect to the other one as a Client
    Serial.print("Connecting to Relay 2...");
    
    WiFi.begin(ssidClient, passwordClient);
    while (WiFi.status() != WL_CONNECTED){
        delay(500);
        Serial.print("Failed! Retrying Connection...");
    }
    Serial.println("\nConnection Success!");

    //Confirmation of this relay IP
    Serial.print("Relay 1 AP IP: ");
    Serial.println(WiFi.softAPIP());

    Serial.print("Relay 1 Client IP: ");
    Serial.println(WiFi.localIP());


    //Configuration of the API requisitions
    server.on("/", HTTP_GET, [](){
        server.send(200, "text/plain", "Relay connected and online");
    });

    server.on("/ON", HTTP_GET, [](){
        digitalWrite(relayPin, LOW);
        server.send(200, "text/plain", "Relay power: ON");
    });
    
    server.on("/OFF", HTTP_GET, [](){
        digitalWrite(relayPin, HIGH);
        server.send(200, "text/plain", "Relay power: OFF");
    });

    server.on("/status", HTTP_GET, [](){
        String status = (digitalRead(relayPin) == LOW) ? "ON" : "OFF";
        server.send(200, "text/plain", "Relay Status: " + status);
    });


    server.begin();
}

//Keeps receiving the requests of new clients
void loop(){
    server.handleClient();
}


