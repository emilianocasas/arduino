#include <avr/sleep.h>
#include <TimeAlarms.h>
#include <Time.h>
#include <Wire.h>
#include <DS1307RTC.h>  

int volatile a = 0;

void setup() {

    Serial.begin(9600);
    pinMode(20, INPUT);
    pinMode(2, INPUT);
    pinMode(A3, INPUT);
    //attachInterrupt(2, funcion, LOW);
    //attachInterrupt(3, funcion, LOW);
}

void loop() {

    if (Serial.available()){
      int valor = Serial.read();
      if (valor == 48){
      if (digitalRead(2)) Serial.println("El 2 esta en HIGH");
      else Serial.println("El 2 esta en LOW");
      }
     
      if (valor == 49){
        setTime(8,29,0,1,1,11);
          if (digitalRead(2)) Serial.println("El 2 esta en HIGH");
      else Serial.println("El 2 esta en LOW");

      }
      }
      if (a==1){
      Serial.println("Entre en la int");
      }
}

void funcion(){
  a = 1;
}


