#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
 
const char* ssid = "6c7334";
const char* password = "268022370";
MDNSResponder mdns;

ESP8266WebServer server(80);


int volatile a = 0;
const int led = 13;

void handleRoot() {
  //digitalWrite(led, 1);
  server.send(200, "text/plain", "ola ke ase");
  //digitalWrite(led, 0);
  a++;
}

void handleNotFound(){
  digitalWrite(led, 1);
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET)?"GET":"POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i=0; i<server.args(); i++){
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
  digitalWrite(led, 0);
}
 
void setup(void){
  pinMode(led, OUTPUT);
  digitalWrite(led, 0);
  Serial.begin(9600);
  WiFi.begin(ssid, password);
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print("."); //Los puntitos esperando a que conecte.. 
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  
  if (mdns.begin("esp8266", WiFi.localIP())) {
    Serial.println("MDNS responder started");
  }
  
  server.on("/", handleRoot);
  
  server.on("/inline", [](){
    server.send(200, "text/plain", "this works as well");
    
    a = 1;
  });

  server.on("/inline2", [](){
    server.send(200, "text/plain", "funciona papu, dejame puntines");
  });


  server.onNotFound(handleNotFound);
  
  server.begin();
  Serial.println("HTTP server started");
}
 
void loop(void){
  server.handleClient();


  if (Serial.available()){
    int valor = Serial.read();
    if (valor == 49){
      Serial.println(a);
    }
  }
     
    
  
} 
