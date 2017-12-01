

void mostrarMensaje(){
  Serial.println("Estoy en la interuppcion");
    delay(1000);
}



void setup() {
  pinMode(2, INPUT);
  digitalWrite(2, LOW);
   Serial.begin(9600);
  attachInterrupt(0, mostrarMensaje, RISING);
}

void loop() {
  if (Serial.available()){
    int val = Serial.read();
    if (val == 49) {
    digitalWrite(2,HIGH);
    delay(1000);
    Serial.println("vengo despues?");
    digitalWrite(2, LOW);
 }
    

}

}
