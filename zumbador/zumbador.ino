#include <TimerThree.h>     

volatile int contador = 0;
void setup() {
  pinMode(A7, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  if (Serial.available()){
    int valor = Serial.read();
    if (valor == 48){
      funcion();
    }
  }

  if (contador == 6){
    digitalWrite(A7, LOW);
    Timer3.detachInterrupt();
    contador = 0;
  }
}

void funcion(){
  Timer3.initialize();
  Timer3.attachInterrupt(contar, 100000);
}

void contar(){
    contador++;
    
    if ((contador % 2) == 0) digitalWrite(A7, LOW);
    else digitalWrite(A7,HIGH);
}







