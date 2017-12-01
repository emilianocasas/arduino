#include <avr/sleep.h>
#include <TimeAlarms.h>
#include <Time.h>
#include <Wire.h>
#include <DS1307RTC.h>  

    int volatile sleepSatus;
    int volatile a = 0;
    int volatile b = 0;
    int contador = 0;
    
    int i = 0;
                                      // pin used for waking up
    int sleepStatus = 0;             // variable to store a request for sleep
    int count = 0;                   // counter
     
    void wakeUpNow(){
      mostrarMensaje();
    }

   void setup(){
      pinMode(6, OUTPUT);
      pinMode(2, INPUT); //Para poder ser usado para la interrupcion
      pinMode(21, INPUT); //Para poder ser usado para la interrupcion
      pinMode(20, INPUT); //Para poder ser usado para la interrupcion
      
      Serial.begin(9600);
      //attachInterrupt(0, wakeUpNow, LOW); // use interrupt 0 (pin 2) and run function
    }
     
    void sleepNow() {
        set_sleep_mode(SLEEP_MODE_PWR_DOWN);  
        sleep_enable();         
        attachInterrupt(2,wakeUpNow, RISING); 
        sleep_mode();           
        sleep_disable();         
        detachInterrupt(0);      
     }
     
    void loop() {
                      
     
     if (Serial.available()) {
        int val = Serial.read();
        if (val == 'S') {
          Serial.println("Serial: Entering Sleep mode");
          delay(100);     // this delay is needed, the sleep
          count = 0;
          sleepNow();     // sleep function called here
        }
       
        if (val == 49) {
          Serial.println("Hola");
        }
          
   }

    }
     


void mostrarMensaje(){
Serial.println("Me desperte");
}


