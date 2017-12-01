void setup() {
  // put your setup code here, to run once:
// pinMode(3, OUTPUT);
 pinMode(13, OUTPUT);
 //pinMode(9, OUTPUT);
 //pinMode(11, OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  
 // digitalWrite(3, HIGH);
  //delay(1000);
  //digitalWrite(3, LOW);
  //delay(1000);
  
  analogWrite(5, 128);
  delay(1000);
  digitalWrite(5, LOW);
  delay(1000);
  

}
