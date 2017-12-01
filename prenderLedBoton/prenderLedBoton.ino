//int contador = 0;
boolean volatile a = 0;
boolean volatile b = 1;

void setup() {
  pinMode(2, INPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  Serial.begin(9600);
  attachInterrupt(0, toggleLed, RISING);

}

void loop() {

  if (Serial.available()){
  int valor = Serial.read();
      if (valor == 49){
        if (digitalRead(2)) 
        Serial.println("El pin 2 esta en HIGH");
        else 
        Serial.println("El pin 2 esta en LOW");
      }
  }

  if (a) digitalWrite(10, HIGH);
  else digitalWrite(10, LOW);

  
  if (b) digitalWrite(11, HIGH);
  else digitalWrite(11, LOW);
  
}  

void toggleLed(){
  a=!a;
  b=!b;
}


