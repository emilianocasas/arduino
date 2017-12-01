#include <TimeAlarms.h>
#include <Time.h>
#include <Wire.h>
#include <DS1307RTC.h>  

int volatile a = 0;

void setup() {
  Serial.begin(9600);
  setTime(8,28,50,1,1,11);
  Serial.println(RTC.get());
  Alarm.alarmRepeat(8,29,0, MorningAlarm);  // 8:30am every day
}

void loop() {
          delay(1000);
         Serial.print(hour());
         printDigits(minute());
         printDigits(second());
         Serial.print(" ");
         Serial.print(day());
         Serial.print(" ");
         Serial.print(month());
         Serial.print(" ");
         Serial.print(year());
         Serial.println();


      if (a == 1){
        Serial.println("Entro en la alarma");
      }
         
}

void MorningAlarm(){
  a = 1;
}


void printDigits(int digits)
   {     Serial.print(":");
         if(digits < 10)
            Serial.print('0');
         Serial.print(digits);
   }
