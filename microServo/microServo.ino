    #include <Wire.h>
    #include <DS3231.h>
     
    DS3231 clock;
    RTCDateTime dt;
     
    void setup()
    {
      Serial.begin(9600);
     
      // Inicjalizacja DS3231
      Serial.println("Initialize DS3231");;
      clock.begin();
     
      // Ustawiamy date i czas z kompilacji szkicu
      clock.setDateTime(__DATE__, __TIME__);
     
      // Lub recznie (YYYY, MM, DD, HH, II, SS
      // clock.setDateTime(2014, 4, 13, 19, 21, 00);
    }
     
    void loop()
    {
      // Odczytujemy czas i formatujemy za pomoca funkcji dateFormat
      dt = clock.getDateTime();
     
      Serial.print("Long number format:          ");
      Serial.println(clock.dateFormat("d-m-Y H:i:s", dt));
     
      Serial.print("Long format with month name: ");
      Serial.println(clock.dateFormat("d F Y H:i:s",  dt));
     
      Serial.print("Short format witch 12h mode: ");
      Serial.println(clock.dateFormat("jS M y, h:ia", dt));
     
      Serial.print("Today is:                    ");
      Serial.print(clock.dateFormat("l, z", dt));
      Serial.println(" days of the year.");
     
      Serial.print("Actual month has:            ");
      Serial.print(clock.dateFormat("t", dt));
      Serial.println(" days.");
     
      Serial.print("Unixtime:                    ");
      Serial.println(clock.dateFormat("U", dt));
     
      Serial.println();
     
      delay(1000);
    }

