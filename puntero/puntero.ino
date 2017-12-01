#include <Wire.h>
#include <DS3231.h>
#include <DS3232RTC.h>    
#include <Time.h> 
#include <avr/sleep.h> 

void setup() {
  Serial.begin(9600);
  volatile int* v = creoVector(5); 
 // llenoVector(v);
 v[0] = 3;
}

void loop() {
 if (Serial.available()){
  int valor = Serial.read();
  if (valor == 49)  {
    Serial.println(v[0]);
  }
 }

}

int* creoVector(int p){
  int* vector[p];
  return vector;
}

void llenoVector(int vec){
  vec[0] = 10;
  vec[1] = 20;
  vec[2] = 30;
  vec[3] = 40;
  vec[4] = 50;
}





int* devolverPunteroInt(int n){
   n = (sizeof(int)) * n;
  int* pointer = (int *)malloc(n);
   return pointer;
  }
  
char* devolverPunteroChar(int n){
   n = (sizeof(char)) * n;
   char* pointer = (char *)malloc(n);
   return pointer;
}

void cargarPuntero(int *p){
  p[0] = 0;
  p[1] = 1;
  p[2] = 2;
  p[3] = 3;
}


void liberarPuntero(int *p){
  free(p);
}


void mostrarPuntero(){
  for (i=0; i<7; i++){
    Serial.println(alarmaDay[i]);
  }
}




