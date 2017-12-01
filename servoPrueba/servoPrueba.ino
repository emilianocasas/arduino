#include <Servo.h> 

Servo myservo;

void setup() {
  myservo.attach(9);
  Serial.begin(9600);
  myservo.write(90);
}

void loop() {
 if (Serial.available()){ 
  int valor = Serial.read();
  if (valor == 49){
  myservo.write(0);
  delay(1000);
  myservo.write(90);
  delay(1000);
 
  }
}
}
