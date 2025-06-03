#include <ESP8266WiFi.h>

void setup(){
    Serial.begin(115200);
    delay(500);
    Serial.println();
    Serial.print("Endereço MAC: ");
    Serial.println(WiFi.macAddress()); 
}