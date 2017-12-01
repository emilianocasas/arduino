void setup() {
  Serial.begin(9600);
  pinMode(10, OUTPUT);
  digitalWrite(10, LOW);

}

void loop() {
  if (Serial.available()) {
      int valor = Serial.read();
      if (valor == 49)  digitalWrite(10, HIGH);
      Serial.println("HIGH enviado");
      //digitalWrite(10,LOW);
  }
}
