void setup() {
  pinMode(10, OUTPUT);
  Serial.begin(9600);

}

void loop() {
  if (Serial.available()){
    int valor = Serial.read();
    if (valor == 48) digitalWrite(10, LOW);
    if (valor == 49) digitalWrite(10, HIGH);
      if (valor == 50) {
    if (digitalRead(10)) Serial.println("10 en high");
    else Serial.println("10 en low");
    }
  }


  
}
