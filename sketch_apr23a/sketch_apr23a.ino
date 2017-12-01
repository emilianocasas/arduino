int datoLectura = 0;

void setup() {
  pinMode(12,OUTPUT);
  Serial.begin(9600);
  Serial.println("Mandar 1 o 0");
  Serial.println("Estoy en el segundo renglon vieja, no me importa nada");
}

void loop() {

 if (Serial.available() > 0) {
    datoLectura = Serial.read();
  }

    
   if (datoLectura == 48){
     Serial.println(datoLectura);
     digitalWrite(12,LOW);
     delay(1000);
    } 
    
    if (datoLectura == 49){
      Serial.println(datoLectura); 
      digitalWrite(12,HIGH);
      delay(1000);  
  } 
    
 
    
   // if (datoLectura == 54){
     //  analogWrite(4, LOW);
    //}
    
}
