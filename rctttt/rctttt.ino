#include <TimeAlarms.h>
#include <Time.h>
#include <Wire.h>
#include <DS1307RTC.h>  // a basic DS1307 library that returns time as a time_t

int volatile a = 0;

void setup()
   {   Serial.begin(9600);
       //while (!Serial) ;              // Solo para el Leonardo
       //setSyncProvider(RTC.get);      // Vamos a usar el RTC
       //Alarm.alarmRepeat(22, 10, 05, function);
       //setTime(22,10,00,22,6,2015); // Las 21:45:00 del dia 8 de Nov de 2014
        //pinMode(10, OUTPUT);
       //if (timeStatus() != timeSet)
         //  Serial.println("Unable to sync with the RTC");
       //else
         //  Serial.println("RTC has set the system time");
   }
void loop()
   {     digitalClockDisplay();
         delay(1000);
         
    if (Serial.available()){
      int valor = Serial.read();
      if (valor == 48){
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
      }
       
    }


if (a==1){
  Serial.println("Alarma prendida");

       }
   }
   
void digitalClockDisplay()
   {    // Serial.print(hour());
        // printDigits(minute());
        // printDigits(second());
        // Serial.print(" ");
        // Serial.print(day());
        // Serial.print(" ");
        // Serial.print(month());
        // Serial.print(" ");
        // Serial.print(year());
        // Serial.println();
   }
void printDigits(int digits)
   {     Serial.print(":");
         if(digits < 10)
            Serial.print('0');
         Serial.print(digits);
   }

void function(){
  a=1;
}


