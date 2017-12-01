#include <SoftwareSerial.h>     //  esp8266
#include <avr/sleep.h>          //  sleep
#include <AccelStepper.h>       //  stepper
#include <Wire.h>               //  wire
#include <DS3231.h>             //  ds3231
#include <DS3232RTC.h>          //  ds3231
#include <Time.h>               //  time
#include <TimerThree.h>         //  timer1
#include <TimerOne.h>           //  timer3

boolean volatile a = false;

void setup() {
  pinMode(2, INPUT_PULLUP);
  Serial.begin(9600);
}

void loop() {
 
  if (Serial.available()){
    int valor = Serial.read();
    if (valor == 49) sleep();
  }
  
  if (a){
    a = false;
    Serial.println("LLUEVE");
  }

  Serial.println("Estoy despierto");
  delay(1000);
  
}

void sleep(){
  Serial.println("Sleep");
  delay(500);
  sleepNow();
}

void sleepNow(){
   set_sleep_mode(SLEEP_MODE_PWR_DOWN);   
   sleep_enable();          
   attachInterrupt(0,wake, LOW);  
   sleep_mode();            
   sleep_disable();         
   detachInterrupt(0); 
}

void wake(){
  Serial.println("wake");
  a = true;
}

