#include <LiquidCrystal.h>
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

String d[6];
String p[8];
volatile int i = 0;
boolean volatile enterFlag = false;

#define pinSi 31
#define pinNo 33
#define pinArriba 14
#define pinAbajo 15
#define pinRealizar 16

#define red A0
#define green A1
#define blue A2

void setup() {
pinMode(red, OUTPUT);
pinMode(green, OUTPUT);
pinMode(blue, OUTPUT);
pinMode(4, INPUT_PULLUP);
pinMode(5, INPUT_PULLUP); 
 
pinMode(pinSi, INPUT_PULLUP);
pinMode(pinNo, INPUT_PULLUP);  
pinMode(pinArriba, INPUT_PULLUP);
pinMode(pinAbajo, INPUT_PULLUP);  
pinMode(pinRealizar, INPUT_PULLUP);

luzApagada();
d[0] = "ROJO ";
d[1] = "VERDE";
d[2] = "AZUL";
d[3] = "CELESTE ";
d[4] = "MAGENTA";
d[5] = "AMARILLO";

p[0] = "FILTRAR";
p[1] = "DESAGOTAR";
p[2] = "RECIRCULAR";
p[3] = "RETROLAVAR";
p[4] = "ENJUAGAR";
p[5] = "TESTEAR";
p[6] = "LAVAR FILTRO";
p[7] = "HACER PRUEBA";
Serial.begin(9600);
lcd.begin(16, 2);           // Fijamos el numero de caracteres y lineas
lcd.print(p[0]);
//luzRoja();
}

void loop(){
   if (digitalRead(pinArriba) == 0) {
      pulseIn(14, HIGH, 300000);
      if (i<7){
       lcd.clear();
       i++;
       delay(100);
       lcd.print(p[i]);
       //delay(100); 
         //if (i==0) luzRoja();
         //if (i==1) luzVerde();
         //if (i==2) luzAzul();
         //if (i==3) luzCeleste();
         //if (i==4) luzMagenta();
         //if (i==5) luzAmarillo();
      }
   } 
   
   if (digitalRead(pinAbajo) == 0) {
     pulseIn(15, HIGH, 200000);
     if (i>0){ 
      lcd.clear();
      i--;
      delay(100);
      lcd.print(p[i]);
     }
    }

    if (digitalRead(pinRealizar) == 0) {
     pulseIn(16, HIGH, 200000);
      
        lcd.clear();
        lcd.print("CONFIRMAR ACCION");
        lcd.setCursor(0,1);
        lcd.print(p[i] + " ?"); 
        enterFlag = true;
     }
    
    if (digitalRead(pinSi) == 0){
      Serial.println("pto control 3");
      if (enterFlag){
         lcd.clear();
         enterFlag = false;
         lcd.print("Empezando operacion");
         delay(1000);
      }
    }

    if (digitalRead(pinNo) == 0){
      if (enterFlag){
         enterFlag = false;
        lcd.clear();
         lcd.print(p[i]);
      }
    }
}

void luzRoja(){
  digitalWrite(red, 0);
  digitalWrite(green, 255);
  digitalWrite(blue, 255);
}

void luzVerde(){
  digitalWrite(red, 255);
  digitalWrite(green, 0);
  digitalWrite(blue, 255);
}

void luzAzul(){
  digitalWrite(red, 255);
  digitalWrite(green, 255);
  digitalWrite(blue, 0);
}

void luzCeleste(){
  digitalWrite(red, 255);
  digitalWrite(green, 0);
  digitalWrite(blue, 0);
}

void luzMagenta(){
  digitalWrite(red, 0);
  digitalWrite(green, 255);
  digitalWrite(blue, 0);
}

void luzAmarillo(){
  digitalWrite(red, 0);
  digitalWrite(green, 0);
  digitalWrite(blue, 255);
}

void luzApagada(){
  digitalWrite(red, 255);
  digitalWrite(green, 255);
  digitalWrite(blue, 255);
}
