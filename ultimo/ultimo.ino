#include <SoftwareSerial.h>
#define DEBUG true
SoftwareSerial Arduino(3,2); 
int i=0;
String r = "";
int contador = 0;
int contadorPin = 0;

void setup() {
  Serial.begin(19200);
  Arduino.begin(19200);
  pinMode(11, OUTPUT);
  digitalWrite(11, LOW);
  pinMode(12, OUTPUT);
  digitalWrite(12, LOW);
  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);
  
    sendData("AT+RST\r\n",2000,DEBUG); // reset module
   sendData("AT+CWMODE=1\r\n",1000,DEBUG); // configure as access point
     for (i=0; i<10; i++){
       delay(1000); 
     }
    sendData("AT+CWLAP\r\n",3000,DEBUG);
     for (i=0; i<10; i++){
       delay(1000); 
     }
    sendData("AT+CWJAP=\"6c7334\",\"268022370\"\r\n ",3000,DEBUG); // me conecto a la red
       for (i=0; i<10; i++){
       delay(1000); 
     }
    sendData("AT+CIFSR\r\n",1000,DEBUG); // get ip address
    sendData("AT+CIPMUX=1\r\n",1000,DEBUG); // configure for multiple connections
    sendData("AT+CIPSERVER=1,80\r\n",1000,DEBUG); // turn on server on port 80
    }


void loop() {
     
    if (Serial.available()){
    Arduino.write(Serial.read());
    }
    
     if (Arduino.available()){
       if (Arduino.find("+IPD,")){
         delay(1000);
         int connectionId = (Arduino.read()) - 48; 
          //if (contador == 0){
          //contador = contador + 1;
          Arduino.find("pin=1");
          int a = (Arduino.read()) - 48;
          Serial.println("Ultimo numero");
          Serial.println(a);
          int pinNumber = a + 10; //Por que el read() lee de a un caracter
          Serial.println("Le sumo 10");
          Serial.println(pinNumber);
            if ((contadorPin % 2) == 0){
                digitalWrite(pinNumber, HIGH);
                contadorPin = contadorPin + 1;
             } else {
                digitalWrite(pinNumber, LOW);
                contadorPin = contadorPin + 1;
             }
          digitalWrite(pinNumber, HIGH);
          //String closeCommand = "AT+CIPCLOSE=";
         // closeCommand+=connectionId; // append connection id
          //closeCommand+="\r\n";
          //sendData(closeCommand,1000,DEBUG); // close connection
          //Serial.println("Conexion cerrada con id: ");
          Serial.println("El connection id tiene un: ");
          Serial.println(connectionId);
          
       }
    }
    
    if (12, HIGH){
       digitalWrite(10, LOW); 
    }
 }

String sendData(String command, const int timeout, boolean debug){
    String response = "";
Arduino.print(command); 
    long int time = millis();
    while( (time+timeout) > millis())
    {
    while(Arduino.available())
    {
    char c = Arduino.read(); 
    response+=c;
    }
    }
    if(debug)
    {
    Serial.print(response);
    }
    return response;
 }

