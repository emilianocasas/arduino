#include <avr/sleep.h>
#include <TimeAlarms.h>
#include <Time.h>
#include <Wire.h>
#include <DS1307RTC.h>  

#define ledRojo 10
#define ledVerde 11
 
int volatile a = 1;
int volatile b = 0;
int count = 0;              

  void prenderLeds(){
      digitalWrite(ledVerde, LOW);
      digitalWrite(ledRojo, HIGH);
  }
     
  
  void mostrarMensajeSerial(){
    Serial.println("Me voy a dormir");
  }
  
  
  void funcion(){
    mostrarMensajeSerial();
      funcion1();
    }

    void funcion1(){
      
      delay(1000);
      delay(1000);
      delay(1000);
      delay(1000);
      delay(1000);
      delay(1000);
      delay(100);
        //prenderLeds();
        sleepNow();
    }


    void setup(){
      Serial.begin(9600);
      pinMode(2, INPUT); 
      pinMode(3, INPUT); 
      pinMode(10, OUTPUT);
      pinMode(11, OUTPUT);
      
      Serial.begin(9600);
      attachInterrupt(0, funcion, RISING); 
     }
     
    void sleepNow() {
        //detachInterrupt(0);     
        set_sleep_mode(SLEEP_MODE_PWR_DOWN);   
        sleep_enable();          
        attachInterrupt(1,wakeUpNow, RISING); 
        sleep_mode();            
        sleep_disable();         
        detachInterrupt(0);      
     }
     
    void loop() {
      if (a){
     
      digitalWrite(ledVerde, HIGH);
   
      //count++;
      //delay(1000);                         
      } else    digitalWrite(ledVerde, LOW);

      
  if (Serial.available()){
    int valor = Serial.read();
    if (valor == 49) {
       Serial.println("Hola");
      }

  }


  }
     
  void wakeUpNow(){
        meDesperte();
        
     }


void meDesperte(){
  Serial.println("Me desperte");
}


     


