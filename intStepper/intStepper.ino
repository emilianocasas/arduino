#include <SoftwareSerial.h>     //  esp8266
#include <avr/sleep.h>          //  sleep
#include <AccelStepper.h>       //  stepper
#include <Wire.h>               //  wire
#include <DS3231.h>             //  ds3231
#include <DS3232RTC.h>          //  ds3231
#include <Time.h>               //  time
#include <TimerThree.h>         //  timer1
#include <TimerOne.h>    

#define motorPin1  8      // IN1 stepper
#define motorPin2  9     // IN2 stepper
#define motorPin3  10     // IN3 stepper
#define motorPin4  11      // IN4 stepper

AccelStepper stepper1(8, motorPin1, motorPin3, motorPin2, motorPin4);
void setup() {
  Serial.begin(9600);
  pinMode(18, INPUT_PULLUP);
  attachInterrupt(5, funcion, FALLING);
  stepper1.setMaxSpeed(1000.0);
  stepper1.setAcceleration(400.0);
  stepper1.setSpeed(300);
  stepper1.move(4070);
}

void loop() {
  //Serial.println(stepper1.distanceToGo());
  stepper1.run();
   
  if (Serial.available()){
    int valor = Serial.read();
    if (valor == 48){
       stepper1.move(4070);
       // while ((stepper1.distanceToGo()) != 0){
       stepper1.runToPosition();
        Serial.println("Hola");  
   //  }
   // Serial.print("Estoy en.. "); Serial.println(stepper1.currentPosition());
     // Serial.print("Tengo que ir a.. "); Serial.println(stepper1.targetPosition());
    } 
      if (valor == 49){
       
       Serial.println("AAAAAA");
      }
  }

  

 // if ((stepper1.distanceToGo()) == 0) Serial.println("LLegue a destino");

}

void funcion(){
  Serial.println("emiliano");
}


