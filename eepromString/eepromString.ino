#include <EEPROM.h>
#include "EEPROMAnything.h"

String s1;
String s2;

int i = 0;
int e;
char c;
int n;

void setup(){
    Serial.begin(9600);
    //n = EEPROM_writeAnything(200, "aguante marama vieja, no me importa nada");
    for (i=200; i<225; i++){
         e = EEPROM.read(i);
         char c = char(e);  
         s1 = String(c);
         s2 += s1;
     }
    Serial.println(s2);
 }
void loop(){


}








