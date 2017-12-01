void setup() {
  pinMode(4, OUTPUT); 
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  Serial.begin(9600);
  analogWrite(4, LOW);
  analogWrite(5, LOW);
  analogWrite(6, LOW);
}

void loop() {
  if (Serial.available()){
  int valor = Serial.read();
  if (valor == 48);
  }
  
  analogWrite(4, LOW);
   analogWrite(5, HIGH);
    analogWrite(6,HIGH);
 
}

