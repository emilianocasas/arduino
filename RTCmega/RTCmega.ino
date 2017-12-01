#include <Time.h>
#include <Wire.h>
#include <DS1307RTC.h>  // La libreria que gestiona el DS1307 RTC para Time

void setup()
   {    Serial.begin(9600);
        //while (!Serial) ;  // Solo si usas un Arduino Leonardo
        setSyncProvider(RTC.get);     // Sincronizar con el RTC
        if(timeStatus()!= timeSet)
             Serial.println("Unable to sync with the RTC");
        else
             Serial.println("RTC has set the system time");
   }
