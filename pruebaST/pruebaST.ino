int volatile a = 0;
int contador = 0;

void setup() {
  pinMode(2, INPUT);
  Serial.begin(9600);
  attachInterrupt(0, funcion, FALLING);
}

void loop() {
  if (Serial.available()){
    int valor = Serial.read();
    if (valor == 49){
      if (digitalRead(2)) Serial.println("2 EN HIGH");
      else Serial.println("2 EN LOW");
    }
  }

  if (a){
    if (contador == 0){
        contador = contador + 1;
        Serial.println("Entre en la int");
    }
  }

}


void funcion(){
  a = 1;
}

