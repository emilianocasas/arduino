#include <avr/sleep.h>        
#include <TimerThree.h>       

int volatile a = 0; 
int volatile b = 0; 
int contador = 0;

void setup() {
  pinMode(2, INPUT);
Serial.begin(9600);
sleepNow();

}

void loop() {

if (Serial.available()) {
    int val = Serial.read();
   
    if (val == 'a') {
      if (digitalRead(2)) Serial.println("El 2 esta en HIGH");
      else Serial.println("El 2 esta en LOW");
      }
}

  
    if (a == 1){
        Timer3.detachInterrupt();
      detachInterrupt(0); 
    contador = 0;
    a = 0;
    Serial.println("Serial: Entering Sleep mode");
    //hagoTiempo();
    delay(1000);
    delay(1000);
    delay(1000);
    sleepNow();     
  }

  if (b == 1){
  Timer3.initialize();
  Timer3.attachInterrupt(contar, 1000000);
  }

  if (contador == 3) {
    contador = 0;
    attachInterrupt(0,sleep, FALLING) ;
  }
}

void sleepNow(){
   set_sleep_mode(SLEEP_MODE_PWR_DOWN);   
   sleep_enable();          
   attachInterrupt(0,wakeBoton, LOW); 
   sleep_mode();            
   sleep_disable();         
   detachInterrupt(0); 
 
}

void contar(){
  Serial.print("Hola, muestro el contador ");
  Serial.println(contador);
  contador++;
}

void wakeBoton(){
  b = 1;
   mostrarMensaje();

}

void mostrarMensaje(){
  Serial.println("Me desperte");
 }

 void sleep(){

 a = 1;
}

void hagoTiempo(){
  contador = 0;
}





