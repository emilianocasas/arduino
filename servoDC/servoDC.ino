void setup() {
  pinMode(9, OUTPUT);
  Serial.begin(9600);

}

void loop() {
  if (Serial.available()){
    int valor = Serial.read();
    if (valor == 48) digitalWrite(9, LOW);
    if (valor == 49) digitalWrite(9, HIGH);
  }

}
