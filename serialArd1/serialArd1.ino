#include <SoftwareSerial.h>

SoftwareSerial esp(10, 11); 

volatile boolean pv_flag = true;
volatile char *comando;
volatile int i = 0;

void setup(){
  Serial.begin(9600); //Para verlo en pantalla 
  esp.begin(9600); // Comunicaion con el arduino

}

void loop(){
  // if (esp.available()){ 
    //  if (pv_flag){
      //  pv_flag = false;
       // i = 0;
      // }
      if (Serial.available()){  
        int valor = Serial.read();
        if (valor != 48){
        comando[i] = esp.read();
         i++; 
        }else{
          Serial.println(*comando);
        }
      }
      
      // }
  }




  

