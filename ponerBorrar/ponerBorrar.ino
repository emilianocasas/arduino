#include <LiquidCrystal.h>
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

void setup() {
  Serial.begin(9600);
  lcd.begin(20, 4);
}

void loop() {
  if (Serial.available()){
    int valor = Serial.read();
    if (valor == 48) poner();
    if (valor == 49) borrar();
  }
}

void poner(){
  int i = 0;
  int d = 0;
  for (i=0; i<4; i++){
      for (d=1; d<17; d++){
        lcd.setCursor(d,i);
        lcd.write("a");
      }
  }
}

void borrar(){
  
  int i = 0;
  int d = 0;
  for (i=0; i<4; i++){
      for (d=1; d<17; d++){
        lcd.setCursor(d,i);
        lcd.write(" ");
      }
  }
}









