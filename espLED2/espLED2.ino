   #include <SoftwareSerial.h>
   #define DEBUG true
   SoftwareSerial esp8266(3,2); 
   int i=0;
   String r = "";
   
    void setup()
    {
    Serial.begin(19200);
    esp8266.begin(19200); // your esp's baud rate might be different
    pinMode(12,OUTPUT);
    digitalWrite(12,LOW);
      sendData("AT+RST\r\n",2000,DEBUG); // reset module
    sendData("AT+CWMODE=1\r\n",1000,DEBUG); // configure as access point
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
    
    void loop(){
      if (esp8266.available()) {
          char a = esp8266.read(); 
          r+=a;
          Serial.print(r);
        if(esp8266.find("+IPD,")){
            delay(1000);
            int connectionId = esp8266.read()-48;
            esp8266.find("pin=");
            int pinNumber = (esp8266.read()-48)*10;
             pinNumber += (esp8266.read()-48);
             digitalWrite(pinNumber, !digitalRead(pinNumber));
        
        }
      }
      
      if (Serial.available())
        esp8266.write(Serial.read());
      
    }      
        

 String sendData(String command, const int timeout, boolean debug)
    {
    String response = "";
    esp8266.print(command); 
    long int time = millis();
    while( (time+timeout) > millis())
    {
    while(esp8266.available())
    {
    char c = esp8266.read(); 
    response+=c;
    }
    }
    if(debug)
    {
    Serial.print(response);
    }
    return response;
    }
