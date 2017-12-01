volatile int  a = 0;
int contador = 0;

void function(){
a=3;
  
}

void setup() {
  Serial.begin(9600);
  //pinMode(3, INPUT_PULLUP);
  //digitalWrite(2, LOW);
  attachInterrupt(1, function , HIGH);
}

void loop() {
  if (Serial.available()){
  int valor = Serial.read();
  if (valor == 49){
  if (digitalRead(2)){
    Serial.println("El pin 2 esta en HIGH");
    } else {
    Serial.println("El pin 2 esta en LOW");
  }
  }
 
  }

//Serial.print("El valor de a es..");
//Serial.println(a);

if (a == 3){
  if (contador == 0){
  Serial.println("Hola"); 
  contador = contador + 1;
}
}




  
}
