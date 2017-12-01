#include <ESP8266WiFi.h>

const char* ssid = "6c7334";
const char* password = "268022370";

WiFiServer server(80);

void setup() {
  pinMode(2, OUTPUT);

  Serial.begin(9600);
  delay(10);
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println();
  Serial.print("Conectado a: "); Serial.println(WiFi.localIP());
  server.begin();
}

void loop() {
  WiFiClient client = server.available(); // Me fijo si se conecto un cliente
  if (!client) {
    return;
  }
  
  while(!client.available()){ //Sigue aca si hay algun cliente, y espera a que envie la info
    delay(1);
  }

  zumbador(2);
  String query = client.readStringUntil('\r'); //Lee la primera linea (por eso el rsu \r) del query del cliente
  client.flush(); //Descarta lo demas (todo lo que no pertenecia a la primera linea)
  int n = query.indexOf("/");
  String aux = query.substring((n+1), query.length());
  n = aux.indexOf(" ");
  String mensaje = aux.substring(0,n);
  digitalWrite(2, LOW);
  Serial.println(mensaje);
  digitalWrite(2, HIGH);
  String s = "Mensaje " + mensaje + " recibido";
  
  client.print(s); //Respuesta al cliente.
  delay(1);
 
}


void zumbador(int n){
  int e = 0;
  for (e=0; e<n; e++){
    digitalWrite(2, HIGH);
    delay(500);
    digitalWrite(2, LOW);
    delay(500);
  } 
}

