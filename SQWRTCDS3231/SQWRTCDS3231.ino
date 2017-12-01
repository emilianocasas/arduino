    #include <Wire.h>
    #include <DS3231.h>
     
    DS3231 clock;
     int volatile a = 0;
    boolean state;
     
    void setup()
    {

    attachInterrupt(0, funcion, FALLING);
      
      pinMode(2, INPUT);
      Serial.begin(9600);
     
      // Inicjalizyjemy DS3231
      Serial.println("Initialize DS3231");;
      clock.begin();
     
      // Wylaczamy wyjscie  32kHz
      clock.enable32kHz(false);
     
      // Ustawiamy wyjscie SQW na sygnal 1Hz
      clock.setOutput(DS3231_1HZ);
     
      // Wlaczamy wyjsscie SQW
      //clock.enableOutput(true);
     
      if (clock.isOutput())
      {
        Serial.println("Oscilator is enabled");
      } else
      {
        Serial.println("Oscilator is disabled");
      }
     
  //    switch (clock.getOutput())
    //  {
      //  case DS3231_1HZ:     Serial.println("SQW = 1Hz"); break;
       // case DS3231_4096HZ:  Serial.println("SQW = 4096Hz"); break;
       // case DS3231_8192HZ:  Serial.println("SQW = 8192Hz"); break;
       // case DS3231_32768HZ: Serial.println("SQW = 32768Hz"); break;
       // default: Serial.println("SQW = Unknown"); break; }
    //}
    }
    void loop(){
      // if (digitalRead(2)) Serial.println("SQW HIGH");
      // else Serial.println("SQW LOW");

      // if (digitalRead(3)) Serial.println("32 HIGH");
      // else Serial.println("32 LOW");
       // Wlaczamy i wylaczamy wyjscie 32kHz co 2 sekundy
      // clock.enable32kHz(state);
      // state = !state;
       //delay(2000);
   
      if (a){
      a = 0;
      Serial.println("Entre en la int");   
    
    }

    }
void funcion(){
  a = 1;
}


