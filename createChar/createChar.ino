#include <LiquidCrystal.h>

LiquidCrystal lcd(7, 8, 9, 10, 11, 12);    

byte rainDrop[8] = {
  0b00000,
  0b00100,
  0b01010,
  0b10001,
  0b10001,
  0b10001,
  0b01110,
  0b00000
};

byte customCharB[8] = {
  0b00000,
  0b00000,
  0b00100,
  0b00110,
  0b11111,
  0b00110,
  0b00100,
  0b00000
};

byte customCharA[8] = {
  0b00000,
  0b00000,
  0b00000,
  0b00000,
  0b11111,
  0b00000,
  0b00000,
  0b00000
};


void setup() {
  lcd.createChar(0, customChar);
  lcd.begin(20, 4);  
  lcd.write(byte(0));

}

void loop() {}

