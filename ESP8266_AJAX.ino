/*
 * ESP8266 NodeMCU AJAX Demo
 * Updates and Gets data from webpage without page refresh
 * https://circuits4you.com
 */
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

#include "index.html.h" //Our HTML webpage contents with javascripts

#define LED D4  //On board LED

//SSID and Password of your WiFi router
const char* ssid = "testESP8266";
const char* password = "123456789";

ESP8266WebServer server(80); //Server on port 80

//===============================================================
// This routine is executed when you open its IP in browser
//===============================================================
void handleRoot() {
 String s = MAIN_page; //Read HTML contents
 server.send(200, "text/html", s); //Send web page
}

void handleADC() {
 int a = analogRead(A0);
 String adcValue = String(a);
 
 server.send(200, "text/plane", adcValue); //Send ADC value only to client ajax request
}

void handleLED() {
  Serial.println("Aqui en agregar");
 String ledState = "Llave agregada exitosamente.";
 server.send(200, "text/plane", ledState); //Send web page
}
//==============================================================
//                  SETUP
//==============================================================
void setup(void){
  Serial.begin(115200);
  pinMode(LED,OUTPUT); 
  // Conectar al WiFi
   WiFi.mode(WIFI_AP);
  while(!WiFi.softAP(ssid, password)){
   Serial.println(".");
    delay(100);
  }

  Serial.print("Iniciado AP ");
  Serial.println(ssid);
  Serial.print("IP address:\t");
  Serial.println(WiFi.softAPIP());

 
  server.on("/", handleRoot);      //Which routine to handle at root location. This is display page
  server.on("/agregar", handleLED);
  server.on("/readADC", handleADC);

  server.begin();                  //Start server
  Serial.println("HTTP server started");
}
//==============================================================
//                     LOOP
//==============================================================
void loop(void){
  server.handleClient();          //Handle client requests
}
