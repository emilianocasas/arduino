#include <TimerOne.h>
#include <TimerThree.h>

int count = 0;

void setup() {
  Serial.begin(9600);
  Timer1.initialize();
  Timer3.initialize();
  //Timer3.setPeriod(2000000); //2s
  //Timer3.attachInterrupt(contar, 2000000);

}

void loop() {
  

}


void funcion(){
  Serial.println("Hola");
}

void contar(){
  count++;
  Serial.println(count);
}

