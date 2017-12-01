void setup() {
  Serial.begin(9600);

}

void loop() {
 if (Serial.available()){
  int valor = Serial.read();
  if (valor == 49){
    if ((14 <= 17) && (17 <= 13)) Serial.println("Verdadero");
    else Serial.println("Falso");
  }
 }
}
