#include <SoftwareSerial.h>

SoftwareSerial esp2866(3, 2); // RX, TX

void setup()
{
// Open serial communications and wait for port to open:
Serial.begin(19200);
esp2866.begin(19200);
}

void loop() // run over and over
{
if (esp2866.available()){
  while (esp2866.available()){
   char c = esp2866.read(); 
    Serial.write(c);  
   }
} 
  
if (Serial.available()){
   delay(1000);
  String command = "";
   while(Serial.available()){
      command+=(char)Serial.read();
   } 
  esp2866.println(command);
 }

}
