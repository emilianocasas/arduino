#include <Servo.h> 

Servo serv;

void setup() {
  serv.attach(9);
  Serial.begin(9600);
   serv.writeMicroseconds(500);
         delay(1000);
   serv.writeMicroseconds(500);
         delay(1000);
   serv.writeMicroseconds(500);
         delay(1000);
}

void loop() {
    if (Serial.available()){
    int valor = Serial.read();
    if (valor == 48){
         serv.write(180);
         delay(1000);
         serv.write(0);
         delay(1000);
         serv.write(180);
         delay(1000);
    }

        if (valor == 49){
         serv.write(90);
         delay(1000);
         serv.write(180);
         delay(1000);
         serv.write(0);
         delay(1000);
         serv.write(180);
         delay(1000);
    }

        if (valor == 50){
         serv.write(0);
         delay(1000);
         serv.write(180);
         delay(1000);
         serv.write(0);
         delay(1000);
         serv.write(180);
         delay(1000);
    }


}
}
