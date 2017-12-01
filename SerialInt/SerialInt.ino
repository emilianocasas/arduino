#include <SoftwareSerial.h>     //  esp8266
#include <avr/sleep.h>          //  sleep
#include <AccelStepper.h>       //  stepper
#include <Wire.h>               //  wire
#include <DS3231.h>             //  ds3231
#include <DS3232RTC.h>          //  ds3231
#include <Time.h>               //  time
#include <TimerThree.h>         //  timer1
#include <TimerOne.h>           //  timer3

volatile boolean flag = false;
volatile boolean lluvia_flag = false;

void setup() {
  pinMode(2, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);
  Serial.begin(9600);
  //sleepA();
}

void loop() {

  if (flag){
    flag = false;
    Serial.println("wake");
  }
    
    if (Serial.available()){
      int valor = Serial.read();
      if (valor == 48) Serial.println("Hola");
      if (valor == 49){
          if (lluvia_flag) sleepB();
        else sleepA();
      }
   
    }

}

void sleepA(){
  Serial.println("Sleep A");
  delay(500);
  sleepNowA();
}

void sleepB(){
  Serial.println("Sleep B");
  delay(500);
  sleepNowB();
}

void sleepNowA(){
   set_sleep_mode(SLEEP_MODE_PWR_DOWN);   
   sleep_enable();          
   attachInterrupt(0,wake, LOW);
   sleep_mode();            
   sleep_disable();         
   detachInterrupt(0); 
}


void sleepNowB(){
   set_sleep_mode(SLEEP_MODE_PWR_DOWN);   
   sleep_enable();          
   attachInterrupt(1,wake, LOW);  
   sleep_mode();            
   sleep_disable();         
   detachInterrupt(1); 
}

void wake(){
   detachInterrupt(0); 
   detachInterrupt(1);
   if (digitalRead(2) == 0) {
    lluvia_flag = true;
    Serial.println("Me desperto 2, llueve");
   }
   if (digitalRead(3) == 0) {
    lluvia_flag = false;
    Serial.println("Me desperto 3, ya no llueve");
   }
    flag = true;
}




