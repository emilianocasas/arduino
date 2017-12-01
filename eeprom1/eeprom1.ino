#include <EEPROM.h>

int i = 0;
int value = 0;

void setup()
{
  Serial.begin(9600);
 // for (i = 0; i < 255; i++)
   EEPROM.write(6, 2000);
}

void loop(){
  
    //for (i = 0; i < 255; i++){
       //value = EEPROM.read(6);
      // Serial.print(i);
        //Serial.print("\t");
          Serial.println(EEPROM.read(6));
          //Serial.println();
    //}
   delay(1000);
}
 
