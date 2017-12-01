volatile boolean a = false;
volatile boolean b = false;

void setup() {
  Serial.begin(9600);
  pinMode(2, INPUT);
  pinMode(3, INPUT_PULLUP);
  pinMode(7, OUTPUT);
  pinMode(8, INPUT);
 // digitalWrite(7, HIGH);
  attachInterrupt(0, funcion0, FALLING);
  //attachInterrupt(1, funcion1, FALLING);
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
      if (digitalRead(8)) Serial.println("8 en high");
      else Serial.println("8 en low");
    }
  }
  
  
  
  if (a){
    a = false;
    Serial.println("Interrupcion pin2");
  }
  if (b){
    b = false;
    Serial.println("Interrupcion pin3");
  }
  
}

void funcion0(){
  a = true;
}

void funcion1(){
  b = true;
}
