void setup() {
  //pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  Serial.begin(9600);

}

void loop() {

  if (Serial.available()){
  int valor = Serial.read();
  if (valor == 48) pinMode(9, OUTPUT);
  if (valor == 49) digitalWrite(10, HIGH);
  }
}
