#include <Wire.h>
#include <DS3231.h>
#include <DS3232RTC.h>    //http://github.com/JChristensen/DS3232RTC
#include <Time.h> 
#include <avr/sleep.h> 

DS3231 clock;
RTCDateTime dt;
volatile boolean b = false;

void setup() {
Serial.begin(9600);
setSyncProvider(RTC.get);   
pinMode(2, INPUT_PULLUP);
//attachInterrupt(0, wake, FALLING);
pinMode(9, OUTPUT);
RTC.squareWave(SQWAVE_NONE);

   clock.setDateTime(2015,7,15, 14, 15, 0);
   // año mes dia hora minuto segundo
   //contadorAux = 1;   
     // RTC.setAlarm(ALM1_MATCH_HOURS, aStartHR[0], 5, 0, 0);
//      segundos, minutos, hora, dia
      RTC.setAlarm(ALM1_MATCH_SECONDS, 5, 0, 0, 0);
      RTC.alarm(ALARM_1);
      RTC.alarmInterrupt(ALARM_1, true);
      //sleep();
     //Serial.println("pto control1");
 }
void loop() {
  dt = clock.getDateTime();
        Serial.print(clock.dateFormat("d-m-Y H:i:s", dt)); Serial.println(digitalRead(2));

  if (RTC.alarm(ALARM_1)) {
     b = true;
 }

       if (b){
        b = false;
        Serial.print("alarma"); Serial.println(digitalRead(2));
       }
    
    delay(1000);
  }







  
