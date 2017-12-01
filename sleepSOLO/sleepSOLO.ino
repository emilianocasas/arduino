#include <SoftwareSerial.h>     //  esp8266
#include <avr/sleep.h>          //  sleep
#include <AccelStepper.h>       //  stepper
#include <Wire.h>               //  wire
#include <DS3231.h>             //  ds3231
#include <DS3232RTC.h>          //  ds3231
#include <Time.h>               //  time
#include <TimerThree.h>         //  timer1
#include <TimerOne.h>           //  timer3

boolean volatile sleepFlag = true;
int volatile contador = 0;
int volatile contador2 = 0;     

#define luzR A0      
#define luzG A1    
#define luzB A2     

void setup() {
  Serial.begin(9600);
  inicializarPines();
  luzRoja();
  

}

void loop(){

if (contador2 == 0){
 if (digitalRead(2)) ;
 else{
  contador2 == 1;
  inicializarTimer1();
 }
}

if (contador == 2){
  contador = 0;
  contador2= 0;
  deshabilitarTimer1();
  luzVerde();
}

 
}

 void luzVerde(){
  analogWrite(luzR, 255);
  analogWrite(luzG, 0);
  analogWrite(luzB, 255);
  delay(1000);
  delay(1000);
  luzRoja();
}

void luzRoja(){
  analogWrite(luzR, 0);
  analogWrite(luzG, 255);
  analogWrite(luzB, 255);
}

void luzAzul(){
  analogWrite(luzR, 255);
  analogWrite(luzG, 225);
  analogWrite(luzB, 0);
}


void inicializarPines(){
  pinMode(luzR, OUTPUT);  
  pinMode(luzG, OUTPUT);
  pinMode(luzB, OUTPUT);
  pinMode(2, INPUT);
}

void sleep(){
  Serial.println("Sleep");
  luzRoja();
  deshabilitarIntSleep();
  sleepFlag = true;
}

void sleepNow(){
   set_sleep_mode(SLEEP_MODE_PWR_DOWN);   
   sleep_enable();       
   luzRoja();   
   attachInterrupt(0,wakeBoton, LOW); 
   sleep_mode();            
   sleep_disable();         
   detachInterrupt(0); 
 }

void habilitarIntSleep(){
  attachInterrupt(0,sleep, FALLING) ;
  Serial.println("int habilitada");
}

void deshabilitarIntSleep(){
  detachInterrupt(0);
}

void wakeBoton(){
  detachInterrupt(0);  
  sleepFlag = false;
  inicializarTimer1();
  luzVerde();
}

void inicializarTimer1(){
  Timer1.initialize();
  Timer1.attachInterrupt(contar, 1000000);
}

void inicializarTimer12(){
  Timer1.initialize();
  Timer1.attachInterrupt(contar, 100000);
}

void contar(){
  if (digitalRead(2)){
      deshabilitarTimer1();
      contador = 0;
      contador2 = 0;
    ;
  }
  else contador++;
}

void deshabilitarTimer1(){
  Timer1.detachInterrupt();
  contador = 0;
}

