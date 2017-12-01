#include <Wire.h>
#include <DS3231.h>
#include <DS3232RTC.h>    
#include <Time.h> 
#include <avr/sleep.h> 


volatile int *alarmaStartHR;

volatile int *alarmaDay;

volatile int *cantAlarmasDia;


volatile int i;


void setup() {

  alarmaDay[0]= 0;
  alarmaDay[1]= 15;
  alarmaDay[2]= 42;
  alarmaDay[3]= 30;
  alarmaDay[4]= 52;
  alarmaDay[5]= 30;
  alarmaDay[6]= 43;
  alarmaDay[7]= 31;

alarmaStartHR[0] = 0; 
  alarmaStartHR[1] = 10;
  alarmaStartHR[2] = 10;
  alarmaStartHR[3] = 13;
  alarmaStartHR[4] = 14;
  alarmaStartHR[5] = 15;
  alarmaStartHR[6] = 20;
   alarmaStartHR[7] = 21;
   
  
 

  cantAlarmasDia[0]= 0;
  cantAlarmasDia[1]= 2;
  cantAlarmasDia[2]= 2;
  cantAlarmasDia[3]= 3;
  cantAlarmasDia[4]= 4;
  cantAlarmasDia[5]= 4;
  cantAlarmasDia[6]= 2;
  cantAlarmasDia[7]= 2;
  Serial.begin(9600);

}

void loop() {
 if (Serial.available()){
  int valor = Serial.read();
  if (valor == 48){
  for (i=0; i<7; i++ ){
    Serial.println(alarmaDay[i+1]);
  }
  i = 0;
 }
  if (valor == 49){
  for (i=0; i<7; i++ ){
    Serial.println(alarmaStartHR[i+1]);
  }
  i = 0;
 }
  if (valor == 50){
  for (i=0; i<7; i++ ){
    Serial.println(cantAlarmasDia[i+1]);
  }
  i = 0;
 }
 }
}
