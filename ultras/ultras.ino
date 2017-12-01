long duration, cm;
 
void setup(){
  Serial.begin(9600);
  pinMode(9, OUTPUT);
  pinMode(8, INPUT);
}
 
void loop(){
  if (Serial.available()){
   int valor = Serial.read();
    if (valor == 49){ 
    digitalWrite(9, LOW);
    delayMicroseconds(2);
    digitalWrite(9, HIGH);
    delayMicroseconds(5);
    //digitalWrite(trigPin, LOW);
    duration = pulseIn(8, HIGH);
 
    cm = microsecondsToCentimeters(duration);
 
    Serial.print ("Milisegundos: ");
    Serial.print(duration);
    Serial.print("  Distancia estimada: ");
    Serial.print(cm);
    Serial.println(" cm");
 
    delay(1000);
    }
 
    }
    }
    long microsecondsToCentimeters(long microseconds){
      // La velocidad del sonido a 20º de temperatura es 340 m/s o
      // 29 microsegundos por centrimetro.
      // La señal tiene que ir y volver por lo que la distancia a
      // la que se encuentra el objeto es la mitad de la recorrida.
      return microseconds / 29 /2 ;
    }
