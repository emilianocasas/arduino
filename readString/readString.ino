#include <LiquidCrystal.h>      

LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

String cadena;

void setup() {
  Serial.begin(9600);
  Serial2.begin(9600);
  lcd.begin(20,4);
  lcd.print("PREPARADO");
}

void loop() {
  if (Serial2.available()){
    cadena = Serial2.readString();
    Serial.println(cadena);
    mostrarCadenaLCD();
  }

}

  void mostrarCadenaLCD(){
    int longitudCad = cadena.length();
    String cadenaFinal = cadena.substring(0,(longitudCad - 2));
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print(cadenaFinal);
  }



