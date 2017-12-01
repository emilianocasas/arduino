//int ledVerde = 11;
//int ledRojo = 9;
int zumbador = 4;


void setup() {
  pinMode(11,OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(zumbador, OUTPUT);

}

void loop() {
  delay(100);
 digitalWrite(11,HIGH);
  digitalWrite(9,HIGH);
  digitalWrite(9,HIGH);
  analogWrite(zumbador, 128);
  delay(500);
  digitalWrite(11,LOW);
  digitalWrite(9,LOW);
  analogWrite(zumbador, LOW);

}
