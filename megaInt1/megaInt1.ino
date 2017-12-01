
int volatile a=0;
int volatile b=0;
int contador = 0;

void funcion(){
  a = 1;
  b = 1;
}

void prenderLed(){
    digitalWrite(6, HIGH);
  delay(1000);
  digitalWrite(6, LOW);
  delay(1000);
}

void setup() {
  pinMode(6, OUTPUT);
  Serial.begin(9600);
  pinMode(2, INPUT);
  attachInterrupt(0, funcion, RISING);
}

void loop() {

  if (Serial.available()){
  int valor = Serial.read();


   if (valor == 48){
    Serial.println("Mando low por 2");
    digitalWrite(2, LOW);
    if (digitalRead(6)) Serial.println("El 6 esta en high");
    else Serial.println("El 6 esta en low");
   }

   if (valor == 49){
    Serial.println("Mando high por 2");
    digitalWrite(2, HIGH);
    if (digitalRead(6)) Serial.println("El 6 esta en high");
    else Serial.println("El 6 esta en low");
   }

   if (valor == 50){
    if (digitalRead(2)) Serial.println("El 2 esta en high");
    else Serial.println("El 2 esta en low");
   }
  
}

  if (a == 1 && contador == 0){
  contador = contador + 1;
  Serial.println("Entre en la int");
    }

    if (b == 1){
   prenderLed();
    }
}

