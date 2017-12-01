void setup() {
  Serial.begin(9600);
  pinMode(7, OUTPUT);
  pinMode(8, INPUT);
}

void loop() {
  if (Serial.available()){
    int valor = Serial.read();
    if (valor == 48){
      Serial.println("Mando low"); 
      digitalWrite(7, LOW);
    }
     if (valor == 49){
      Serial.println("Mando high"); 
      digitalWrite(7, HIGH);
    }
    if (valor == 50){
      if (digitalRead(8)) Serial.println("8 en HIGH");
      else Serial.println("8 en LOW");
      }
    }
  }


