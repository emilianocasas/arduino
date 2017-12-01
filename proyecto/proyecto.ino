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
int sleepStatus = 0;             // variable to store a request for sleep
int count = 0;                   // counter
     
    void wakeUpNow(){
      a=1;
      b=1;
    }


      void toggleLed(){
        digitalWrite(6, HIGH);
        delay(1000);
        digitalWrite(6, LOW);
        delay(1000);
      }
 
     
    void setup(){
      pinMode(6, OUTPUT);
      pinMode(2, INPUT); //Para poder ser usado para la interrupcion
      pinMode(21, INPUT); //Para poder ser usado para la interrupcion
      pinMode(20, INPUT); //Para poder ser usado para la interrupcion
      
      Serial.begin(9600);
      //attachInterrupt(0, wakeUpNow, LOW); // use interrupt 0 (pin 2) and run function
    }
     
  
     
    void loop() {
      Serial.print("Awake for ");
      Serial.print(count);
      Serial.println("sec");
     count++;
      delay(1000);                         
     
     if (Serial.available()) {
        int val = Serial.read();
        if (val == 'S') {
          Serial.println("Serial: Entering Sleep mode");
          delay(100);     // this delay is needed, the sleep
          count = 0;
          sleepNow();     // sleep function called here
        }
       
        if (val == 48) {
          digitalWrite(6, LOW);
        }
        if (val == 49) {
          digitalWrite(6, HIGH);
        }
          if (val == 50){
           if (digitalRead(2)) Serial.println("El 2 esta en high");
            else Serial.println("El 2 esta en low");
   }
   if (val == 51) {
          toggleLed();
        }
  
      }
     
      // check if it should go to sleep because of time
      //if (count >= 50) {
        //  Serial.println("Timer: Entering Sleep mode");
          //delay(100);     // this delay is needed, the sleep
          //count = 0;
          //sleepNow();     // sleep function called here
     // }

      
  if (a == 1 && contador == 0){
  contador = contador + 1;
  Serial.println("Entre en la int");
    }

  if (b == 1){
  digitalWrite(6, HIGH);
  delay(1000);
  digitalWrite(6, LOW);
  delay(1000);
    }
    }
     


void funcion(){

Serial.println("Me desperto el rtc");


}

void MorningAlarm(){
Serial.println("Morning alarm");
}

void dormir() {
        set_sleep_mode(SLEEP_MODE_PWR_DOWN);   // seteo modo sleep
        sleep_enable();                        // libera el sleepbit del registro mcu
        //A continuacion hago referencia a las interrupciones que pueden despertar al arduino
        attachInterrupt(0,despertarBoton, HIGH);      // pushButton
        attachInterrupt(1,despertarRTC, HIGH);      // RTC
        attachInterrupt(2,despertarESP, HIGH);      // esp8266-07
        sleep_mode();                          // Aca el arduino realmente duerme
        //Desde aca empieza a ejecutar luego de despertarse
        sleep_disable();         
        //Desato las interrupciones, para que accidentalmente no se disparen cuando el arduino esta despierto
        detachInterrupt(0);// pushButton
        detachInterrupt(1);// RTC
        detachInterrupt(2);// esp8266-07
}


void despertarBoton(){
  // Si el arduino esta encendido, este boton lo apaga, excepto que se este realizando alguna accion, entonces 
  // debe esperar a que esta termine. 
  // 
}




     
