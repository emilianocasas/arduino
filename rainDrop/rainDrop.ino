#include <LiquidCrystal.h>
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

boolean volatile a = true;
boolean volatile b = true;

void setup() {
  pinMode(A0, INPUT);
  pinMode(2, INPUT_PULLUP);
  attachInterrupt(0, rain, FALLING);
  Serial.begin(9600);
  lcd.begin(17, 2);
}

void loop() {

      if (digitalRead(4) == 0) {
 //       if (a){
   //     lcd.clear();
     //   a = false;
       // b = true;
       //lcd.print("LLUEVE ");  lcd.print(analogRead(A0));
      // }
      }else {
        if (b){ 
        lcd.clear();
        b = false;
        a = true;
        //lcd.print("NO LLUEVE" + analogRead(A0));
        lcd.print("NO LLUEVE "); lcd.print(analogRead(A0));
      }

   }

    Serial.println(analogRead(A0));
    delay(1000);
}

void rain(){
  lcd.clear();
  lcd.print("LLUEVE ");  lcd.print(analogRead(A0));
}

