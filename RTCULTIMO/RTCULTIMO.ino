#include <Wire.h>
#include <DS3231.h>

int volatile a = 0;

DS3231 clock;
RTCDateTime dt;

void setup(){
  pinMode(2, INPUT);
  Serial.begin(9600);
  clock.begin();
  clock.setDateTime(2014, 7, 11, 15, 50, 10);
  clock.armAlarm1(false);
  clock.clearAlarm1();
  clock.setAlarm1(0, 0, 0, 20, DS3231_MATCH_S);
   
  //clock.enable32kHz(false);
 // clock.setOutput(DS3231_1HZ);
  //clock.enableOutput(true);

 // switch (clock.getOutput()){
   // case DS3231_1HZ:     Serial.println("SQW = 1Hz"); break;
   // case DS3231_4096HZ:  Serial.println("SQW = 4096Hz"); break;
   // case DS3231_8192HZ:  Serial.println("SQW = 8192Hz"); break;
   // case DS3231_32768HZ: Serial.println("SQW = 32768Hz"); break;
   // default: Serial.println("SQW = Unknown"); break; 
    //}
}



void loop(){
  dt = clock.getDateTime();
  Serial.println(clock.dateFormat("d-m-Y H:i:s", dt));
  if (clock.isAlarm1()) Serial.println("ALARM 1 TRIGGERED!");
  
  if (digitalRead(2)) Serial.println("2 EN HIGH");
  else Serial.println("2 EN LOW");

  if (a){
    a = 0;
    Serial.println("INTERRUPCION");
  }

  
  delay(250);
}


void funcionAlarma(){
 a = 1; 
}





