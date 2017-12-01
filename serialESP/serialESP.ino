#include <SoftwareSerial.h>

SoftwareSerial ard1(10, 11); 
char *comando;
int i = 0;
boolean pv_flag = true;
boolean respuesta_flag = false;

void setup() {
  Serial.begin(9600);
  ard1.begin(9600);

}

void loop() {
  if (ard1.available()) {
    if (pv_flag){
     respuesta_flag = true;
      pv_flag = false;
     // i=0;
      Serial.println("Aparezco una vez");
    }
    char c = ard1.read();
    Serial.write(c);
    Serial.println("x");
    //comando[i] = ard1.read();
    //Serial.write(comando[i]);   
    //i++;
  }
  
  if (respuesta_flag){
    pv_flag = true;
    respuesta_flag = false;
  }
  
  if (Serial.available()){
    int valor = Serial.read();
    if (valor == 48) {
      //Serial.write(comando);
      i = 0;
      Serial.println("i en 0");
    }
  }

}





