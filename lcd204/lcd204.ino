#include <LiquidCrystal.h>
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

int i = 0;

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

void setup() {
  lcd.createChar(0, rainDrop);
  lcd.begin(20, 4);
}

void loop() {
  for (i=0; i<20; i++){
    lcd.setCursor(i,0);
    lcd.write(byte(0));
    lcd.setCursor(i,3);
    lcd.write(byte(0));
  }

  for (i=0; i<4; i++){
    lcd.setCursor(0,i);
    lcd.write(byte(0));
    lcd.setCursor(19,i);
    lcd.write(byte(0));
  }

}





