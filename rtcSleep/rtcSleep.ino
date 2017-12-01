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
int count = 0;                

void setup(){
 pinMode(6, OUTPUT);
 pinMode(2, INPUT); 
 pinMode(21, INPUT); 
 pinMode(20, INPUT); 
      
 Serial.begin(9600);
 }
     
void sleepNow() {
 set_sleep_mode(SLEEP_MODE_PWR_DOWN);   
 sleep_enable();          
 setearRTC();
 attachInterrupt(2,funcion, HIGH); 
 attachInterrupt(3,funcion, HIGH); 
 sleep_mode();            
 sleep_disable();         
 detachInterrupt(2);
 detachInterrupt(3);      
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
          delay(100);     
          count = 0;
          sleepNow();     
        }
        if (val == 48) {
          digitalWrite(6, LOW);
        }
        if (val == 49) {
          digitalWrite(6, HIGH);
        }
        if (val == 50) {
           if (digitalRead(2)) Serial.println("El 2 esta en high");
            else Serial.println("El 2 esta en low");
   }
  
      }
  }
     
void funcion(){

Serial.println("Me desperto el rtc");


}

void MorningAlarm(){
Serial.println("Morning alarm");
}

void setearRTC(){

}
 

