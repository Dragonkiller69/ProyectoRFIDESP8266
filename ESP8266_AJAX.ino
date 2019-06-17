/*
 * ESP8266 NodeMCU AJAX Demo
 * Updates and Gets data from webpage without page refresh
 * https://circuits4you.com
 */
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <RFIDMIPS135.h>
#include "index.html.h" //Our HTML webpage contents with javascripts

#define LEDverde D3
#define LEDrojo D2
#define Relay D8
#define BUZZER D0

RFID rfid(LEDverde, LEDrojo, BUZZER, Relay);

//SSID and Password of your WiFi router
const char *ssid = "testESP8266";
const char *password = "123456789";
String indexhtml = MAIN_page; // String que contiene la pagina completa
String estado;
boolean agregando = false;

ESP8266WebServer server(80); //Server on port 80

//===============================================================
// This routine is executed when you open its IP in browser
//===============================================================
void handleRoot()
{
  server.send(200, "text/html", indexhtml); //envia la pagina para renderizar en el navegador
}

void handleGetUID(){
  agregando = true;
  rfid.getUIDSecure();
  server.send(200, "text/plane", rfid.UID);
}

void handleAgregar()
{
  agregando = false;
  Serial.println("Aqui en agregar");
  if (rfid.addCard()){
    estado = "Llave agregada exitosamente";
  }else{
    estado = "La llave ya existe";
  }
  server.send(200, "text/plane", estado); //Send web page
}

//==============================================================
//                  SETUP
//==============================================================
void setup(void){
  
  // Conectar al WiFi
  WiFi.mode(WIFI_AP);
  while (!WiFi.softAP(ssid, password))
  {
    Serial.println(".");
    delay(100);
  }

  Serial.print("Iniciado AP ");
  Serial.println(ssid);
  Serial.print("IP address:\t");
  Serial.println(WiFi.softAPIP());

  /*
  Estas instrucciones se encargan de manejar las peticiones del cliente
  dependiendo del path q soliciten
  */
  server.on("/", handleRoot); 
  server.on("/agregar", handleAgregar);
  server.on("/getuid", handleGetUID);

  server.begin(); //Start server
  Serial.println("HTTP server started");
}
//==============================================================
//                     LOOP
//==============================================================

void loop(void){
  server.handleClient(); //Maneja las peticiones de cliente

  if(!agregando){
     rfid.operarCerradura();
    }
        
}
