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
const char *ssid = "chapaNFC";
const char *password = "12345678";
 
ESP8266WebServer server(8000); //Server on port 8000
 

//==============================================================
//                  SETUP
//==============================================================

void setup() {
  Serial.begin(115200);
  delay(10);
  
  WiFi.mode(WIFI_AP);
  while(!WiFi.softAP(ssid, password)){
   Serial.println(".");
    delay(100);
  }
  
  Serial.print("Iniciado AP ");
  Serial.println(ssid);
  Serial.print("IP address:\t");
  Serial.println(WiFi.softAPIP());
 
  //Onboard LED port Direction output
  pinMode(LED,OUTPUT);

  server.on("/micro2019", handleRoot);      //Which routine to handle at root location. This is display page
  server.on("/setLED", handleLED);
  server.on("/leerADC", handleADC);
 
  server.begin();                  //Start server
  Serial.println("HTTP server started");
  
}
//==============================================================
//                     LOOP
//==============================================================
void loop(void){
  server.handleClient();          //Escucha las peticiones del cliente
}

//===============================================================
// This routine is executed when you open its IP in browser
//===============================================================
void handleRoot() {
 String s = MAIN_page; //s sería igual a todo el contenido de index.html.h
 server.send(200, "text/html", s); //Mostramos la pagina en el navegador
 Serial.println(s);
}
 
void handleADC() {
 int a = analogRead(A0);
 String adcValue = String(a);
 
 server.send(200, "text/plane", adcValue); //Enviamos el valor recogido en el pin A0
}
 
void handleLED() {
 String ledState = "OFF";
 String t_state = server.arg("LEDstate"); //Referencia a xhttp.open("GET", "setLED?LEDstate="+led, true);
 Serial.println(t_state);
 if(t_state == "1")
 {
  digitalWrite(LED,HIGH); //LED ON
  ledState = "ON"; //Cambiamos el estado
 }
 else
 {
  digitalWrite(LED,LOW); //LED OFF
  ledState = "OFF"; //Se cambia el estado
 }
 
 server.send(200, "text/plane", ledState); //Envias estado a la pagina
}
